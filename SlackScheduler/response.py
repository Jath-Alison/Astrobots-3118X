import os
import re
from flask import Flask, request
from slack_sdk import WebClient
from slack_bolt import App, Say
from slack_bolt.adapter.flask import SlackRequestHandler

app = Flask(__name__)

client = WebClient(token='xoxb-630789612963-5695330586003-VQE11ANGyQbW0iGCFRR4MT3n')
bolt_app = App(token='xoxb-630789612963-5695330586003-VQE11ANGyQbW0iGCFRR4MT3n', signing_secret='9127aac2d7f1658074bd16178c7177fe')

@app.route("/scheduler/events", methods=["POST"])
def slack_events():
    """ Declaring the route where slack will post a request """
    return handler.handle(request)


@bolt_app.message("hello slacky")
def greetings(payload: dict, say: Say):
    """ This will check all the message and pass only those which has 'hello slacky' in it """
    user = payload.get("user")
    say(f"Hi <@{user}>")

@bolt_app.message(re.compile("(hi|hello|hey) slacky"))
def reply_in_thread(payload: dict):
    """ This will reply in thread instead of creating a new thread """
    response = client.chat_postMessage(channel=payload.get('channel'),
                                     thread_ts=payload.get('ts'),
                                     text=f"Hi<@{payload['user']}>")

handler = SlackRequestHandler(bolt_app)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)