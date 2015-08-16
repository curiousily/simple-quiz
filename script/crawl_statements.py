from bs4 import BeautifulSoup
import requests
import json
from random import shuffle

def get_other_pages(current_page):

    html = requests.get(current_page).text

    soup = BeautifulSoup(html)

    return [link.get('href') for link in soup.find(id='pagelist').find_all('a')
            if link.get('href') != '#']

def get_statements_from_page(page, correct_answer):
    html = requests.get(page).text

    soup = BeautifulSoup(html)
    statements = soup.p.get_text().split('\n')
    statements = filter(None, statements)
    return [(statement, correct_answer) for statement in statements]

all_statements = []
domain_name = 'http://funny2.com/'

pages = ['falsefacts.htm']
#pages.extend(get_other_pages(domain_name + pages[0]))

#for page in pages:
#    all_statements.extend(get_statements_from_page(domain_name + page, False))

#with open('statements.json', 'a+') as statements_file:
#    json.dump(all_statements, statements_file)

js_file = open('statements.json')
data = json.load(js_file)
#print(len(data))
shuffle(data)
with open('statements-data.json', 'w+') as statement_file:
    json.dump(data, statement_file)
#print(data)
js_file.close()
