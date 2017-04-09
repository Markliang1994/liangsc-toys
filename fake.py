#coding=utf-8
from selenium import webdriver
from time import sleep
import traceback

TICKET_URI = 'https://kyfw.12306.cn/otn/leftTicket/init'
LOGIN_URI = 'https://kyfw.12306.cn/otn/login/init'
MY_URI = 'https://kyfw.12306.cn/otn/index/initMy12306'
LOGIN = u'登录'

from splinter.browser import Browser
from time import sleep
import traceback

TICKET_URI = 'https://kyfw.12306.cn/otn/leftTicket/init'
LOGIN_URI = 'https://kyfw.12306.cn/otn/login/init'
MY_URI = 'https://kyfw.12306.cn/otn/index/initMy12306'
LOGIN = 'login_user'

def login():
    brw.find_element_by_id(LOGIN).click()
    sleep(3)

    uname = '123456789@qq.com'
    pwd = 'xxxyyyzzz'

    brw.find_element_by_id('username').send_keys(uname)
    sleep(1)
    brw.find_element_by_id('password').send_keys(pwd)
    sleep(1)

    while True:
        if brw.current_url != MY_URI:
            sleep(1)
        else:
            break

def addCookie(cklist):
    li = list()
    for d in cklist:
        if d['name'] == '_jc_save_toStation' or d['name'] == '_jc_save_toDate' or d['name'] == '_jc_save_fromStation':
            li.append(d)
    return li

def book():
    global brw

    brw = webdriver.Chrome()
    brw.set_window_size(1366, 768)
    brw.get(TICKET_URI)

    sleep(3)

    while brw.find_element_by_id(LOGIN):
        login()
        if brw.current_url == MY_URI:
            break;

    try:
        brw.get(TICKET_URI)
        sleep(2)
        # set src
        brw.find_element_by_id('fromStationText').clear()
        brw.find_element_by_id('fromStationText').click()
        brw.find_element_by_id('fromStationText').send_keys(u'合肥南')
        sleep(3)

        # set dst
        brw.find_element_by_id('toStationText').clear()
        brw.find_element_by_id('toStationText').click()
        brw.find_element_by_id('toStationText').send_keys(u'武汉')
        sleep(3)

        # set left date
        print('please click train date')
        sleep(5)

        cke = brw.get_cookies()
        li = addCookie(cke)
        for x in li:
            brw.add_cookie(x)

        brw.refresh()

        count = 0
        success = False
        if not success:
            while brw.current_url == TICKET_URI:
                brw.find_element_by_id('query_ticket').click()
                sleep(2)
                print(u'第%d次刷新' % count)
                count += 1
                brw.find_element_by_partial_link_text('D3057')

    except Exception as e:
        print(traceback.print_exc())

if __name__ == "__main__":
    book()
