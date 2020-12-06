import random

# Савченко Е.С., 2020

male_names = "Ярослав Денис Геннадий Вячеслав "\
"Степан Леонид Виталий Матвей "\
"Иннокентий Михаил Артём Святослав "\
"Фёдор Никита Тимур Кирилл "\
"Илья Геннадий Илья Данила "\
"Николай Ярослав Ростислав Максим".split(" ")
male_surnames = "Вралов Прокудин Гончаров Гайдовский "\
"Кашинцов Левшин Баратов Недобров "\
"Тюменский Зиновьев Давидов Некрасов "\
"Жуковский Ширинский Булдаков Чаплыгин "\
"Горняковский Вельяшев Мельгунов Мономахов "\
"Водов Замятнин Карабчевский Дубровин Адамович".split(" ")
male_patronymics = "Павлович Аркадьевич Вячеславович Денисович "\
"Игоревич Борисович Евгеньевич Тимофеевич "\
"Валентинович Денисович Филиппович Иванович "\
"Николаевич Фёдорович Сергеевич Матвеевич "\
"Евгеньевич Павлович Геннадьевич Валентинович "\
"Артемович Георгиевич Андреевич Григорьевич".split(" ")

female_names = "Анжела Наталья Виктория Агния "\
"Диана Елена Ольга Мария "\
"Алёна Зоя Марья Зинаида "\
"Маргарита Наталья София Людмила "\
"Арина Евгения Зинаида Екатерина "\
"Ольга Марина Вероника Валерия".split(" ")
female_surnames = "Бестужева Салтыкова Ивашкина Рублёва "\
"Микешина Пинская Селиверстова Юрьева "\
"Александрович Зинчук Прокудина Чаадаева "\
"Чемоданова Головченко Каблукова Водынская "\
"Голофеева Горихвостова Матчина Улыбышева "\
"Бекетова Кочетова Хрущова Тростенская Гарткевич".split(" ")
female_patronymics = "Матвеевна Сергеевна Кирилловна Максимовна "\
"Эдуардовна Романовна Руслановна Владимировна "\
"Борисовна Артёмовна Витальевна Максимовна "\
"Павловна Валериевна Евгеньевна Георгиевна "\
"Матвеевна Данииловна Ивановна Руслановна "\
"Евгеньевна Геннадьевна Вячеславовна Владиславовна".split(" ")

def generate_full_name():
    name_base = random.choice(((male_names, male_surnames, male_patronymics), (female_names, female_surnames, female_patronymics)))
    return random.choice(name_base[1]) + " " + random.choice(name_base[0]) + " " + random.choice(name_base[2])

def generate_phone_number():
    return "+375" + random.choice(("29", "44", "33", "25")) + str(random.randint(0, 10_000_000)).zfill(7)

towns = "Минск Гомель Могилёв Витебск "\
"Гродно Брест Бобруйск Барановичи "\
"Борисов Пинск Орша Мозырь "\
"Новополоцк Солигорск Лида Молодечно "\
"Полоцк Жлобин Светлогорск Речица "\
"Жодино Слуцк Кобрин Слоним "\
"Волковыск Калинковичи Сморгонь Рогачёв "\
"Осиповичи Горки".split(" ")

streets = "Центральная Молодежная Школьная Лесная "\
"Советская Новая Садовая Набережная "\
"Заречная Зеленая Мира Ленина "\
"Полевая Луговая Октябрьская".split(" ")

def generate_address():
    return f"г. {random.choice(towns)} ул. {random.choice(streets)} д. {random.randint(1, 100)} кв. {random.randint(1, 100)}"

def generate_passport_id():
    return "".join([random.choice("0123456789QWERTYUIOPASDFGHJKLZXCVBNM") for _ in range(14)])

with open("readers.txt", "w") as f:
    for i in range(1, 101):
        print(generate_full_name(), file=f)
        print(generate_phone_number(), file=f)
        print(generate_address(), file=f)
        print(generate_passport_id(), file=f)
        print(i, file=f)

print("Генерация завершена.")
        
