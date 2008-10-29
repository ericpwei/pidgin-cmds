/*
 * purple-grep plugin
 *
 * by eric wei
 *
 * blah blah licensing mumbo jumbo blah blah
 */

#define PLUGIN_STATIC_NAME "grep"

#include <glib.h>

#include <purple.h>
#include <plugin.h>
#include <version.h>

/* Bad header dependency : cmds.h must be included after internal.h and plugin.h */
#include <cmds.h>

#include <string.h>

#define GREP_PLUGIN_ID "core-purple-grep"

static PurpleCmdId grep_plugin_id;
static const PurpleMessageFlags CONVERSATION_FLAGS = PURPLE_MESSAGE_SEND | PURPLE_MESSAGE_RECV;
static const PurpleMessageFlags WRITE_FLAGS        = PURPLE_MESSAGE_NO_LOG | PURPLE_MESSAGE_SYSTEM;

static PurpleCmdRet
grep_command_cb(PurpleConversation *conv, const char *cmd, char **args, char **error, gpointer null)
{
	GList *message_history = g_list_last(purple_conversation_get_message_history(conv));
	time_t _time = time(NULL);
  
	for (; message_history; message_history = message_history->prev) {
		PurpleConvMessage *message = message_history->data;
		
		if (purple_conversation_message_get_flags(message) & CONVERSATION_FLAGS) {
			if (strstr(purple_conversation_message_get_message(message), args[0])) {
				time_t timestamp = purple_conversation_message_get_timestamp(message);
				char *display_message = 
					g_strdup_printf("%s %s: %s", 
							purple_utf8_strftime("(%H:%M:%S)", 
									     localtime(&timestamp)),
							purple_conversation_message_get_sender(message),
							purple_conversation_message_get_message(message));
				
				if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_IM) {
					purple_conv_im_write(PURPLE_CONV_IM(conv), NULL, 
							     display_message, WRITE_FLAGS, _time);
				} else if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_CHAT) {
					purple_conv_chat_write(PURPLE_CONV_CHAT(conv), NULL, 
							       display_message, WRITE_FLAGS, _time);
				}
				
				g_free(display_message);
			}
		}
	}
	
	return PURPLE_CMD_STATUS_OK;
}


static void
grep_plugin_init(PurplePlugin *plugin)
{
	grep_plugin_id = 0;
}

static gboolean
grep_plugin_load(PurplePlugin *plugin)
{
	grep_plugin_id = purple_cmd_register("grep", "S", PURPLE_CMD_P_DEFAULT,
				       PURPLE_CMD_FLAG_CHAT | PURPLE_CMD_FLAG_IM, NULL,
				       grep_command_cb, 
				       "grep &lt;string&lt;: search current conversation for string", 
				       NULL);

	return TRUE;
}

static gboolean
grep_plugin_unload(PurplePlugin *plugin)
{
	if (grep_plugin_id) {
		purple_cmd_unregister(grep_plugin_id);
		grep_plugin_id = 0;
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
	
	GREP_PLUGIN_ID,                              /**< id             */
	"Purple-Grep",                               /**< name           */
	VERSION,                                     /**< version        */
	/**  summary        */
	"Enable /grep command",
	/**  description    */
	"Search current conversation for a string",
	"Eric Wei <ericwei.dev@gmail.com>",          /**< author         */
	NULL,                                        /**< homepage       */
	
	grep_plugin_load,                            /**< load           */
	grep_plugin_unload,                          /**< unload         */
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

PURPLE_INIT_PLUGIN(PLUGIN_STATIC_NAME, grep_plugin_init, info)
