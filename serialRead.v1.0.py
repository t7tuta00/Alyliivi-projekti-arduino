import serial
import time
import sys
import os
import json
import requests
import smtplib

#Config
serial_port = '/dev/ttyACM0'

#Communication
ser = serial.Serial(serial_port, 9600, dsrdtr = 1, rtscts = 1)
ser.flushInput()
API_ENDPOINT = "XXXXX"
API_KEY = "XXXXX"
time.sleep(0.15)
turha = 'Falling had happend, help patient\r\n'

#luo text.txt filen alyliivi-projektikansioon
while 1:
    Ntc = ser.readline()
    StateInfo = ser.readline()
    data = {'Temp': Ntc,
            'State': StateInfo} 
    print(json.dumps(data))
    turha2 = data['State']
    
    if turha2 == turha:
        r = requests.post(url = API_ENDPOINT, headers = {'content-type': 'application/json'}, data = json.dumps(data))
        gmail_user = 'XXXXX'
        gmail_password = 'XXXXX'

        sent_from = gmail_user
        to = ['XXXXX']
        subject = 'Halytys'
        body = 'Potilas on kaatunut'

        email_text = """\
        From: %s
        To: %s
        Subject: %s

        %s
        """ %(sent_from, ", ".join(to), subject, body)

        try:
            server = smtplib.SMTP_SSL('smtp.gmail.com',465)
            server.ehlo()
            server.login(gmail_user, gmail_password)
            server.sendmail(sent_from, to, email_text)
            server.close()
            print 'email sent!'
            
        except:
            print 'failed to send email'

