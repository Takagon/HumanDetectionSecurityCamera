#!/usr/bin/env python3
import os
import sys
import rospy
from std_msgs.msg import Int32
import time

from smtplib import SMTP
from email.mime.text import MIMEText
from email import encoders
from email.mime.base import MIMEBase
from email.mime.multipart import MIMEMultipart

def sendGmailAttach():
    sender, password = "hoge@gmail.com", "hoge"
    to = 'home@gmail.com'
    sub = 'detected an invader'
    body = 'invader image'
    host, port = 'smtp.gmail.com', 587

    msg = MIMEMultipart()
    msg['Subject'] = sub
    msg['From'] = sender
    msg['To'] = to

    body = MIMEText(body)
    msg.attach(body)

    attach_file = {'name': 'face_dst.jpg', 'path': '/robosys_ws/src/robosys_pkg/src/faceimages/face_dst.jpg'}
    attachment = MIMEBase('image', 'png')
    file = open(attach_file['path'], 'rb+')
    attachment.set_payload(file.read())
    file.close()
    encoders.encode_base64(attachment)
    attachment.add_header("Content-Disposition", "attachment", filename=attach_file['name'])
    msg.attach(attachment)

    gmail=SMTP("smtp.gmail.com", 587)
    gmail.starttls()
    gmail.login(sender, password)
    gmail.send_message(msg)

def callback(data):
    rospy.loginfo(rospy.get_caller_id()+" I heard %d",data.data)
    print(data.data)
    if data.data == 1:
        sendGmailAttach()
        print('mail send')

if __name__ == "__main__":
    rospy.init_node('flagslistener')
    rospy.Subscriber("faceflag", Int32, callback)
    rospy.spin()