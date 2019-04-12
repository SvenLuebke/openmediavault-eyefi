<?php

/**
 * Copyright (C) 2009-2013 Volker Theile <volker.theile@openmediavault.org>
 * Copyright (C) 2013-2017 OpenMediaVault Plugin Developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

class OMVModuleEyeFi extends \OMV\Engine\Module\ServiceAbstract
    implements \OMV\Engine\Notify\IListener, \OMV\Engine\Module\IServiceStatus
{
	/**
	 * Get the module name.
	 *
	 * @return string
	 */
	public function getName()
	{
        return "eyefiserver";
	}

	/**
	 * Generate the configuration.
     * @throw E_EXEC_FAILED
	 */
	public function applyConfig()
	{
        $cmd = new \OMV\System\Process("omv-mkconf", "eyefiserver");
        $cmd->setRedirect2to1();
        $cmd->execute();
	}

    public function startService()
    {
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get("conf.service.eyefiserver");
        if (TRUE !== $object->get("enable"))
            return;
        // Start this service and enable the unit file.
        $systemCtl = new \OMV\System\SystemCtl("eyefiserver");
        $systemCtl->enable(TRUE);
    }

    public function stopService()
    {
        $systemCtl = new \OMV\System\SystemCtl("eyefiserver");
        $systemCtl->disable(TRUE);
    }

	/**
	 * Get the module status.
	 */
    public function getStatus()
    {
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get("conf.service.eyefiserver");
        $systemCtl = new \OMV\System\SystemCtl("eyefiserver");
        return array(
            "name" => $this->getName(),
            "title" => gettext("EyeFiServer"),
            "enabled" => $object->get("enable"),
            "running" => $systemCtl->isActive()
        );
    }

	/**
	 * Helper function to find out whether the given shared folder
	 * configuration object is used. If it is used, then mark the
	 * module as dirty.
	 * @param type The event message type.
	 * @param path The event message path.
	 * @param object The configuration object.
	 */
	final public function onSharedFolder($type, $path, $object)
    {
        $db = \OMV\Config\Database::getInstance();
        if (TRUE === $db->exists("conf.service.eyefiserver.share", [
            "operator" => "stringEquals",
            "arg0" => "upload_dir",
            "arg1" => $object['uuid']
        ])) {
            $this->setDirty();
        }
    }

	/**
	 * Bind listeners.
	 */
	public function bindListeners(\OMV\Engine\Notify\Dispatcher $dispatcher)
	{
		// Add listeners here. The most common thing is to monitor configuration
		// changes on the service. When the config is changed the module
		// sets itself as dirty (as seen below). Setting a module as dirty
		// makes the apply button appear in the web interface (which in turn
		// calls the applyConfig function on each module with a dirty state).
        $dispatcher->addListener(
            OMV_NOTIFY_MODIFY,
            "org.openmediavault.conf.service.eyefiserver",
            [ $this, "setDirty" ]
        );
        $dispatcher->addListener(
            OMV_NOTIFY_CREATE | OMV_NOTIFY_MODIFY | OMV_NOTIFY_DELETE,
            "org.openmediavault.conf.service.eyefiserver.share",
            [ $this, "setDirty" ]
        );
        $dispatcher->addListener(
            OMV_NOTIFY_MODIFY,
            "org.openmediavault.conf.system.sharedfolder",
            [ $this, "onSharedFolder" ]
        );
        $dispatcher->addListener(
            OMV_NOTIFY_MODIFY,
            "org.openmediavault.conf.system.sharedfolder.privilege",
            [ $this, "onSharedFolder" ]
        );
	}
}