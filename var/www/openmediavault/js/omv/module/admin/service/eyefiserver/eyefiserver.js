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

// Register a node in the navigation tree.
//
// id:
//     Set the ID of the node.
// path:
//     Parent path in the navigation view.
// Text:
//     Service name/title. This is displayed in the navigation.
// icon16:
//     16x16 pixel icon that is displayed in the navigation tree.
// iconSvg:
//     SVG icon that is displayed in the navigation view.
OMV.WorkspaceManager.registerNode({
    id: "eyefiserver",
    path: "/service",
    text: _("Eye-Fi"),
    icon16: "images/eyefiserver.png",
    iconSvg: "images/eyefiserver.svg"
});