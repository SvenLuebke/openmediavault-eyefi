/**
 * @license   http://www.gnu.org/licenses/gpl.html GPL Version 3
 * @author    Volker Theile <volker.theile@openmediavault.org>
 * @author    OpenMediaVault Plugin Developers <plugins@omv-extras.org>
 * @copyright Copyright (c) 2009-2013 Volker Theile
 * @copyright Copyright (c) 2013-2017 OpenMediaVault Plugin Developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
// require("js/omv/WorkspaceManager.js")
// require("js/omv/workspace/form/Panel.js")

Ext.define("OMV.module.admin.service.eyefiserver.Settings", {
    extend: "OMV.workspace.form.Panel",

    rpcService   : "eyefiserver",
    rpcGetMethod : "getSettings",
    rpcSetMethod : "setSettings",

    // getFormItems is a method which is automatically called in the
    // instantiation of the panel. This method returns all fields for
    // the panel.
    getFormItems: function() {
        return [{
            // xtype defines the type of this entry. Some different types
            // is: fieldset, checkbox, textfield and numberfield.
            xtype: "fieldset",
            title: _("General settings"),
            fieldDefaults: {
                labelSeparator: ""
            },
            // The items array contains items inside the fieldset xtype.
            items: [{
                xtype: "checkbox",
                // The name option is sent together with is value to RPC
                // and is also used when fetching from the RPC.
                name: "enable",
                fieldLabel: _("Enable"),
                // checked sets the default value of a checkbox.
                checked: false
            },
            {
                xtype: "textfield",
                name: "card_mac_address",
                fieldLabel: _("Card MAC address"),
                allowDecimals: true,
                allowBlank: false
            },
            {
                xtype: "textfield",
                name: "upload_key",
                fieldLabel: _("Upload key"),
                allowDecimals: true,
                allowBlank: false
            },
            {
                xtype: "sharedfoldercombo",
                name: "upload_dir",
                fieldLabel: _("Upload folder"),
                allowNone: false,
                plugins: [{
                  ptype: "fieldinfo",
                  text: Ext.String.format("{0} {1}",
                    _("The location of the files where new images are uploaded."),
                    _("Please make sure that the shared folder is publicly writable if new files are allowed."))
                }]
            },
            {
                xtype: "textfield",
                name: "sub_directory_schema",
                fieldLabel: _("Sub directory schema"),
                plugins: [{
                  ptype: "fieldinfo",
                  text: Ext.String.format("{0} {1}",
                    _("The subfolder for each transferred picture."),
                    _("It can contain a strftime formatted string."))
                }],
                allowDecimals: true,
                allowBlank: false
            },
            {
                xtype: "textfield",
                name: "upload_user",
                fieldLabel: _("Upload user"),
                allowDecimals: false,
                allowBlank: false
            },
            {
                xtype: "textfield",
                name: "upload_group",
                fieldLabel: _("Upload group"),
                allowDecimals: false,
                allowBlank: false
            }
            ]
        }];
    }
});

// Register a panel into the GUI.
//
// path:
//     We want to add the panel in our example node.
//     The node was configured with the path /service and the id example.
//     The path is therefore /service/example.
//
// className:
//     The panel which should be registered and added (refers to
//     the class name).
OMV.WorkspaceManager.registerPanel({
    id: "settings",
    path: "/service/eyefiserver",
    text: _("Settings"),
    position: 10,
    className: "OMV.module.admin.service.eyefiserver.Settings"
});

