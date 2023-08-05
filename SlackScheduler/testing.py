""" Basic operations using Slack_sdk """

import os
from slack_sdk import WebClient 
from slack_sdk.errors import SlackApiError 

""" We need to pass the 'Bot User OAuth Token' """
slack_token = 'xoxb-630789612963-5695330586003-VQE11ANGyQbW0iGCFRR4MT3n' #os.environ.get('SLACK_BOT_TOKEN')
slack_secret = "9127aac2d7f1658074bd16178c7177fe"
# print (slack_token)
# Creating an instance of the Webclient class
client = WebClient(token=slack_token)

try:
    # Posting a message in #random channel
    response = client.chat_postMessage(
                    channel="scheduler_testing",
                    text="Bot's first message")

    # Sending a message to a particular user
    # response = client.chat_postEphemeral(
    #                 channel="scheduler_testing", 
    #                 text="Hello U02EGB2CWRK", 
    #                 user="U02EGB2CWRK")
    # Get basic information of the channel where our Bot has access 
    # response = client.conversations_info(channel="C05LFAANN6P")

    # # Get a list of conversations
    # response = client.conversations_list()
    # print(response["channels"])
	
except SlackApiError as e:
    print("error")
    assert e.response["error"]
	