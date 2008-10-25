/*
 * pidgin-shout plugin
 *
 * by eric wei
 *
 * blah blah licensing mumbo jumbo blah blah
 */

#define PLUGIN_STATIC_NAME "shout"

#include <glib.h>

#include <purple.h>
#include <plugin.h>
#include <version.h>

/* Bad header dependency : cmds.h must be included after internal.h and plugin.h */
#include <cmds.h>

#define SHOUT_PLUGIN_ID "core-pidgin-shout"

static PurpleCmdId shout_plugin_id;
static PurpleCmdRet shout_command_cb(PurpleConversation *, const char *, char **, char **, void *);

static PurpleCmdRet
shout_command_cb(PurpleConversation *conv,
		     const char *cmd, char **args, char **error, void *data)
{
	GList *conversation_it = NULL;
	for (conversation_it = purple_get_conversations(); 
	     conversation_it; 
	     conversation_it = conversation_it->next) {
		PurpleConversation *current_conversation = conversation_it->data;
		
		if (purple_conversation_get_type(current_conversation) == PURPLE_CONV_TYPE_IM) {
			purple_conv_im_send(PURPLE_CONV_IM(current_conversation), args[0]);
		} else if (purple_conversation_get_type(current_conversation) == PURPLE_CONV_TYPE_CHAT) {
			purple_conv_chat_send(PURPLE_CONV_CHAT(current_conversation), args[0]);
		}
	}

	return PURPLE_CMD_RET_OK;
}

static void
shout_plugin_init(PurplePlugin *plugin)
{
	shout_plugin_id = 0;
}

static gboolean
shout_plugin_load(PurplePlugin *plugin)
{
	shout_plugin_id = purple_cmd_register("shout", "S", PURPLE_CMD_P_DEFAULT,
					      PURPLE_CMD_FLAG_CHAT | PURPLE_CMD_FLAG_IM, NULL,
					      shout_command_cb, 
					      "shout &lt;message&gt;: /say a message to all conversations",
					      NULL);

	return TRUE;
}

static gboolean
shout_plugin_unload(PurplePlugin *plugin)
{
	if (shout_plugin_id) {
		purple_cmd_unregister(shout_plugin_id);
		shout_plugin_id = 0;
	}

	return TRUE;
}

static PurplePluginInfo info =
{
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,                      /**< type           */
	NULL,                                        /**< ui_requirement */
	0,                                           /**< flags          */
	NULL,                                        /**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,                     /**< priority       */
	
	SHOUT_PLUGIN_ID,                             /**< id             */
	"Pidgin-Shout",                              /**< name           */
	VERSION,                                     /**< version        */
	/**  summary        */
	"Enable /shout command",
	/**  description    */
	"/say a message to all open conversations",
	"Eric Wei <ericwei.dev@gmail.com>",          /**< author         */
	NULL,                                        /**< homepage       */
	
	shout_plugin_load,                           /**< load           */
	shout_plugin_unload,                         /**< unload         */
	NULL,                                        /**< destroy        */
	
	NULL,                                        /**< ui_info        */
	NULL,                                        /**< extra_info     */
	NULL,
	NULL,
	/* Padding */
	NULL,
	NULL,
	NULL,
	NULL
};

PURPLE_INIT_PLUGIN(PLUGIN_STATIC_NAME, shout_plugin_init, info)
