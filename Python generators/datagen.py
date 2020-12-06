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
    return "+375" + random.choice(("29", "44", "33", "25")) + str(random.randint(0, 9_999_999)).zfill(7)

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

document_types = ["Книга", "Автореферат диссертации", 
                  "Статья", "Нотный документ",
                  "Диссертация"]

document_topics = "о мышах.о законах РБ.о квантовых технологиях.об импортозамещении."\
                  "об обязанностях служащих.о церквях.о контактах с разумными системами."\
                  "о поляризационных свойствах многомодовых градиентных световодов со слабой анизотропией."\
                  "о птицах. о рыбах. о животных. о грибах. о физике. об оформлении курсовых работ."\
                  "о лекарственных препаратах.об анализе рынка.о стихах Пушкина.о советской государственности."\
                  "о военной топографии.о многомерных бубликах.о заболеваниях.о теории игр.о логике.о генерации случайных документов".split('.')

def generate_document_name(t):
    return document_types[t] + " " + random.choice(document_topics)

with open("readers.txt", "w") as f:
    for i in range(1, 101):
        print(generate_full_name(), file=f)
        print(generate_phone_number(), file=f)
        print(generate_address(), file=f)
        print(generate_passport_id(), file=f)
        print(i, file=f)

with open("authors.txt", "w") as f:
    for i in range(1, 51):
        print(generate_full_name(), file=f)
        print(i, file=f)

with open("documents.txt", "w") as f:
    for i in range(1, 101):
        t = random.randint(0, 4)
        print(t, file=f)
        l = random.randint(0, 10)
        print(l, file=f)
        print(random.randint(1, 13), file=f)
        print(generate_document_name(t), file=f)
        print(random.randint(1, 2000), file=f)
        print(i, file=f)

with open("document_author_binds.txt", "w") as f:
    for i in range(1, 201):
        print(random.randint(1, 100), file=f)
        print(random.randint(1, 50), file=f)

with open("document_use_records.txt", "w") as f:
    for i in range(1, 801):
        print(random.randint(1, 100), file=f)
        print(random.randint(1, 100), file=f)
        print(random.randint(1_262_278_080, 1_607_255_000), file=f)
        print(random.randint(1, 720), file=f)

print("Генерация завершена.")
        
