import requests
import urllib

BOT_TOKEN = "5704987969:AAGXeIY0VXaAUaACoqiYibM-mv2Q6sa41hU"

while True:
    updates_url = 'https://api.telegram.org/bot{}/getUpdates?offset=-1'.format(BOT_TOKEN)
    updates_resp = requests.get(updates_url)
    
    updates_datos = updates_resp.json()

    if len(updates_datos["result"]) > 0:
        if updates_datos["result"][0]["message"]["text"] == "/start":
            chat_id = updates_datos["result"][0]["message"]["chat"]["id"]

            response_text = 'Su+ID+es+{}.+Complete+el+formulario+de+su+dispotivo+con+este+ID.'.format(chat_id)
            response_url = 'https://api.telegram.org/bot{}/sendMessage?chat_id={}&text={}'.format(BOT_TOKEN, chat_id, response_text)

            resp = requests.get(response_url)

        reset_update_id = str(int(updates_datos["result"][0]["update_id"]) + 1)
        requests.get('https://api.telegram.org/bot{}/getUpdates?offset={}'.format(BOT_TOKEN, reset_update_id))