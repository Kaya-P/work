from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from selenium.common.exceptions import NoSuchElementException, TimeoutException
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import time

driver = webdriver.Chrome(ChromeDriverManager().install())
# access twitter
url = r'https://twitter.com/login'
driver.get(url)
f = open('output.txt', 'w')

# helperfunction for wait time


def waiting(by_var, att):
    try:
        WebDriverWait(driver, 20).until(
            lambda x: x.find_element(by=by_var, value=att))
    except (NoSuchElementException, TimeoutException):
        print('{} {} not found'.format(by_var, att))
        exit()


waiting('name', 'session[username_or_email]')

login_email = driver.find_element_by_name('session[username_or_email]')
login_password = driver.find_element_by_name('session[password]')
login_email.send_keys('********')
login_password.send_keys('******', Keys.ENTER)

waiting('css selector', "a[aria-label = Profile]")
profile = driver.find_element_by_css_selector("a[aria-label='Profile']")
profile.click()

# navigate to tweets and replies if no tweets
# waiting(
#     'xpath', "/html/body/div/div/div/div[2]/main/div/div/div/div/div/div[2]/div/div/nav/div/div[2]/div/div[2]/a")
# twt_rpl = driver.find_element_by_xpath(
#     "/html/body/div/div/div/div[2]/main/div/div/div/div/div/div[2]/div/div/nav/div/div[2]/div/div[2]/a")
# twt_rpl.click()

SCROLL_PAUSE = 3.0
path = []

while True:
    waiting('css selector', "[aria-label='View Tweet activity']")
    prev_height = driver.execute_script(" return document.body.scrollHeight")
    elements = driver.find_elements_by_css_selector(
        "a[aria-label = 'View Tweet activity']")
    path.extend([element.get_attribute('href') for element in elements])
    driver.execute_script("window.scrollTo(0, {})".format(prev_height + 500))
    time.sleep(SCROLL_PAUSE)
    # get height to see if more tweets have loaded
    new_height = driver.execute_script("return document.body.scrollHeight")
    if (new_height == prev_height):
        break
# for each element in the path
# change to the inframe for the tweet analytics

for p in path:
    driver.get(p)
    # not available iframe
    waiting('tag name', 'iframe')
    iframe = driver.find_element_by_tag_name('iframe')
    driver.switch_to.frame(iframe)
    detail = driver.find_element_by_tag_name('body')
    # get impressions
    waiting('class name', 'ep-MetricTopContainer')
    impression = detail.find_element_by_class_name('ep-MetricTopContainer')
    f.write(impression.text)
    f.write('\n')
    # get engagement
    try:
        WebDriverWait(driver, 3).until(
            lambda x: x.find_element(by='class name', value='ep-ViewAllEngagementsButton'))
    except TimeoutException:
        continue
    all_engagement = driver.find_element_by_class_name(
        'ep-ViewAllEngagementsButton')
    all_engagement.click()
    waiting('class name', 'ep-EngagementsSection')
    engagesection = driver.find_element_by_class_name(
        'ep-EngagementsSection')
    waiting('class name', 'ep-MetricTopContainer')
    engagement = engagesection.find_element_by_class_name(
        'ep-MetricTopContainer')
    f.write(engagement.text)
    f.write('\n')
    waiting('class name', 'ep-DetailedEngagementsSection')
    detail = engagesection.find_element_by_class_name(
        'ep-DetailedEngagementsSection')
    waiting('class name', 'ep-SubSection')
    engagement_details = detail.find_elements_by_class_name('ep-SubSection')
    for _ in engagement_details:
        f.write(_.text)
        f.write('\n')
f.close()
# create table for tweets

