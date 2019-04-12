<?php
/**
 * Copyright (C) 2009-2013 Volker Theile <volker.theile@openmediavault.org>
 * Copyright (C) 2013-2019 OpenMediaVault Plugin Developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

class OMVRpcServiceEyeFi extends \OMV\Rpc\ServiceAbstract
{
	/**
	 * Get the name of the RPC service.
	 *
	 * @return string
	 */
	public function getName()
	{
		return "eyefiserver";
	}

	/**
	 * Initialize the RPC service. The RPC methods are registered in this
	 * function with $this->registerMethod.
	 *
	 * @return void
	 */
	public function initialize()
	{
		$this->registerMethod("getSettings");
		$this->registerMethod("setSettings");
	}

    public function getSettings($params, $context)
    {
        // Validate the RPC caller context.
        $this->validateMethodContext($context, ["role" => OMV_ROLE_ADMINISTRATOR]);
        // Get the configuration object.
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get("conf.service.eyefiserver");
        return $object->getAssoc();
	}

    public function setSettings($params, $context)
    {
        // Validate the RPC caller context.
        $this->validateMethodContext($context, ["role" => OMV_ROLE_ADMINISTRATOR]);
        // Validate the parameters of the RPC service method.
        $this->validateMethodParams($params, "rpc.eyefiserver.setsettings");
        // Get the existing configuration object.
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get("conf.service.eyefiserver");
        $object->setAssoc($params);
        $db->set($object);
        // Return the configuration object.
        return $object->getAssoc();
    }
}