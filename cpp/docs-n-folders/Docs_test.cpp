#include <iostream>
#include "Docs.h"

using namespace std;
using namespace doc;

void functionTest1();
void functionTest2();
void functionTest3();
void functionTest4();
void functionTest5();
void functionTest6();
void functionTest7();
void functionTest8();
void functionTest9();
void functionTest10();
void functionTest11();
void functionTest12();
void functionTest13();
void functionTest14();
void functionTest15();
void functionTest16();
void functionTest17();
void functionTest18();

typedef void (*functionTest)();

void testPause() {
    getchar();
}

int main() {
    #ifdef IS_WIN
    system("chcp 1251 > nul");
    #endif
    cout << "Тестирование системы классов ДОКУМЕНТЫ И ПАПКИ" << endl;
    cout << "Автор: Слимов Никита, ИУ5-23 (апрель-июнь 2015)" << endl;

    const char *functions[] = {
        "Создание контейнерных объектов для папок документов, в которых могут размещаться документы этой папки",
        "Создание объектов для документов с параметрами",
        "Создание объектов для документов на основе других",
        "Создание объектов для даты создания и изменения документов, которые могут сравниваться между с собой, выводиться в формате ГГГГ-ММ-ДД ЧЧ:ММ:СС",
        "Создание объектов для авторов и редакторов документов, которые хранят имя автора",
        "Учет следующих свойств документа: название документа, размер документа, путь в файловой системе к файлу (в котором хранится содержание документа), тип документа, дата создания документа, дата последнего изменения документа, автор документа, автор последнего изменения документа",
        "Задание и получение характеристик документа",
        "Разделение документов по следующим типам: приказ, протокол, решение, договор, письмо, справка, счет, норма (стандарт), закон, статья, книга, карта, архив. а также тип другой документ для всех остальных документов",
        "Перегрузить операторы присваивания для документов, папок, даты изменения документа и автора документа",
        "Распечатка характеристик документа",
        "Учет следующих свойств папки: название папки, число документов в папке, создатель папки, автор последнего изменения свойств папки или автор последнего добавления документа в папку или удаления документа из папки",
        "Распечатка списка документов папки, в том числе и с разделением документов по типам из пункта 5.1.8",
        "Задание и получение характеристик папки",
        "Добавление документа в папку и удаление документа из папки",
        "Сложение двух папок (создание новой папки, в которой хранятся все документы из обеих сложенных папок)",
        "Сложение папки и документа (создание новой папки, в которой хранятся все документы из первой папки и документ, который складывается)",
        "Вычитание папки из папки (создание новой папки, в которой хранятся документы из первой папки, которых нет во второй папке)",
        "Вычитание документа из папки (создание новой папки, в которой хранятся все документы из папки кроме одного – документа, который вычитается)"
    };

    functionTest functionTests[] = {
        &functionTest1, &functionTest2, &functionTest3,
        &functionTest4, &functionTest5, &functionTest6,
        &functionTest7, &functionTest8, &functionTest9,
        &functionTest10, &functionTest11, &functionTest12,
        &functionTest13, &functionTest14, &functionTest15,
        &functionTest16, &functionTest17, &functionTest18};

    int functionsCount = sizeof(functions)/sizeof(char*);

    while(true) {
        cout << endl << "============ Меню тестирования ============" << endl;
        for(int i = 0; i < functionsCount; i++) {
            cout << (i+1) << ". " << functions[i] << endl;
        }
        cout << "0. выход" << endl;
        cout << ">>>> ";

        int mode;
        cin >> mode;
        cin.clear(); cin.sync();

        if(mode == 0) {
            break;
        }

        if(mode > 0 && mode <= functionsCount) {
            #ifdef IS_WIN
            system("cls");
            #else
            system("clear");
            #endif
            cout << "{{{{{ -------------------------------------------------------  " << endl;
            cout << "{{{{{ -----------------  ";
            cout << "ТЗ 5.1." << mode << endl;
            cout << functions[mode-1] << endl << endl;
            (*functionTests[mode-1])();
            cout << endl << "  ----------------- }}}}}" << endl;

            testPause();
            cout << endl << "  Тестирование пункта " << mode << " завершено";
            cout << endl << "  ------------------------------------------------------- }}}}}" << endl;
            testPause();
            #ifdef IS_WIN
            system("cls");
            #else
            system("clear");
            #endif
        }
        else
        {
            cout << "Введено недопустимое значение, повторите ввод!" << endl;
        }
    }

    return 0;
}

void functionTest1() {
    cout << "Компания начинает новый проект Альянс. \nДля этого проекта необходимы следующие документы: договор, счета, ГОСТ, рекламная статья." << endl;

    testPause();

    cout << "Создаем новую папку \"Проект Альянс\"." << endl;
    DocumentFolder folder1("Проект Альянс", DocumentAuthor("Матвеев Алексей", "Руководитель"));
    cout << folder1;

    testPause();
    
    cout << "Создаем новые документы" << endl;
    Document
        doc1("Договор Профи", Contract, 200),
        doc2("Счет сентябрь 2014", Bill, 100),
        doc3("Счет октябрь 2014", Bill, 172),
        doc4("ГОСТ 17474-80", Standart, 1700),
        doc5("Реклама газета", Article, 1900);
    cout << doc1 << doc2 << doc3 << doc4 << doc5;

    testPause();

    cout << "Добавляем новые документы в папку" << endl;
    folder1.add(doc1);
    folder1.add(doc2);
    folder1.add(doc3);
    folder1.add(doc4);
    folder1.add(doc5);
    cout << folder1;

    testPause();

    cout << "Получим документ с индексом 2" << endl;
    Document *d1 = (Document*) folder1[2];
    cout << *d1;

    testPause();

    cout << "Получим документ с названием Счет октябрь 2014" << endl;
    Document *d2 = (Document*) folder1["Счет октябрь 2014"];
    cout << *d2;

    testPause();

    cout << "Получим все документы папки и распечатаем каждый из них" << endl;
    int count1 = 0;
    Document **ds1 = (Document**) folder1.getDocuments(count1);
    for(int i = 0; i < count1; i++) {
        cout << *ds1[i];
    }
    delete[] ds1;

    testPause();
    
    cout << "Получим документы типа Счет и распечатаем каждый из них" << endl;
    int count2 = 0;
    Document **ds2 = (Document**) folder1.getDocuments(getDocumentTypeByName("Счет"), count2);
    for(int i = 0; i < count2; i++) {
        cout << *ds2[i];
    }
    delete[] ds2;
}
void functionTest2() {
    cout << "Данные о документах компании могут полными или неполными. \nСистема классов позволяет создавать объекты документов со всеми полями или только с частью из них." << endl;

    testPause();

    cout << "Создаем пустой документ" << endl;
    Document doc1;
    cout << doc1;

    testPause();
    
    cout << "Создаем документ с названием Руководство пользователя" << endl;
    Document doc2("Руководство пользователя");
    cout << doc2;

    testPause();
    
    cout << "Создаем документ типа Письмо с названием Письмо Президенту" << endl;
    Document doc3("Письмо Президенту", Letter);
    cout << doc3;

    testPause();

    cout << "Создаем документ типа Карта с названием Москва, размером 4500 байт и указываем путь к нему: /Карты России/МОСКВА.jpg" << endl;
    Document doc4("Москва", Map, 4500, "/Карты России/МОСКВА.jpg");
    cout << doc4;

    testPause();

    cout << "Создаем документ типа Закон с названием Налоговый Кодекс, размером 3945 байт, \nуказываем путь к нему: /Законы/Налоги.doc, указываем дату создания 25 марта 2015 и автора-создателя Большаков Иван (юрист)" << endl;
    Document doc5("Закон", Law, 3945, "/Законы/Налоги.doc", "2015-03-25", DocumentEditor("Большаков Иван", "Юрист"));
    cout << doc5;
}
void functionTest3() {
    cout << "При учете документов в компании часто одни документы похожи на другие. \nЧтобы не создавать документы заново, достаточно скопировать старый документ и изменить некоторые свойства." << endl;
    
    testPause();

    cout << "Создаем документ типа Счет с названием Счет Альянс март 2015, размером 37 байт, \nуказываем путь к нему: /Счета/2015/март/Альянс.xls, указываем дату создания 1 марта 2015 и автора-создателя Васильева Александра (бухгалтер)" << endl;
    Document doc1("Счет Альянс март 2015", Bill, 37, "/Счета/2015/март/Альянс.xls", "2015-03-01", DocumentEditor("Васильева Александра", "Бухгалтер"));
    cout << doc1;

    testPause();

    cout << "Создаем документ на основе уже созданного" << endl;
    cout << "Меняем месяц в названии на апрель, дату создания и путь в файловой системе" << endl;
    Document doc2(doc1);
    doc2.setTitle("Счет Альянс апрель 2015");
    doc2.setPath("/Счета/2015/апрель/Альянс.xls");
    doc2.setCreatedDate(DocumentDate("2015-04-01"));
    cout << doc2;

    testPause();

    cout << "Выводим информацию о первом документе, чтобы убедиться, что его свойства не изменились." << endl;
    cout << doc1;

}
void functionTest4() {
    cout << "Для каждого созданного документа могут учитываться свойства: дата создания и дата последнего изменения." << endl;

    testPause();

    cout << "Возможна ситуация, когда дата создания или дата изменения неизвестны." << endl;
    DocumentDate date1;
    cout << date1 << endl;

    testPause();

    cout << "При редактировании часто нужно указывать текущую дату." << endl;
    DocumentDate date2(false);
    cout << date2 << endl;

    testPause();

    cout << "Создаем объект для даты 25 марта 1997" << endl;
    DocumentDate date3("1997-03-25");
    cout << date3 << endl;

    testPause();

    cout << "Создаем объект для даты 25 марта 1997 и указываем время - 15:34:16" << endl;
    DocumentDate date4("1997-03-25 15:34:16");
    cout << date4 << endl;

    testPause();

    cout << "Сравним даты: 25 мая 2015 и 30 мая 2015" << endl;
    DocumentDate date5("2015-05-25"), date6("2015-05-30");
    cout << date5 << (date5 > date6 ? " > " : " < ") << date6 << endl;
    cout << date6 << (date6 > date5 ? " > " : " < ") << date5 << endl;
}
void functionTest5() {
    cout << "При учете документов важно сохранять, кто создал и кто редактировал документы." << endl;

    testPause();

    cout << "Создадим пустой объект автора/редактора документа" << endl;
    DocumentEditor editor1;
    cout << editor1;

    testPause();

    cout << "Создадим объект автора/редактора документа с именем Большаков Иван" << endl;
    DocumentEditor editor2("Большаков Иван");
    cout << editor2;

    testPause();

    cout << "Создадим объект автора/редактора документа с именем Васильева Александра и должностью Бухгалтер" << endl;
    DocumentEditor editor3("Васильева Александра", "Бухгалтер");
    cout << editor3;
}
void functionTest6() {
    cout << "Создаем документ типа Счет с названием Счет Альянс март 2015, размером 37 байт, \nуказываем путь к нему: /Счета/2015/март/Альянс.xls, указываем дату создания 1 марта 2015 и автора-создателя Васильева Александра (бухгалтер)" << endl;
    cout << "Укажем последнего редактора документа - Матвеев Алексей (руководитель), который изменил документ 25 марта 2015 года." << endl;
    Document doc1("Счет Альянс март 2015", Bill, 37, "/Счета/2015/март/Альянс.xls", "2015-03-01", DocumentEditor("Васильева Александра", "Бухгалтер"));
    doc1.setEditor(DocumentEditor("Матвеев Алексей", "Руководитель"));
    doc1.setEditedDate("2015-03-25");
    cout << doc1;
}
void functionTest7() {
    cout << "Каждое свойство документа может изменяться в процессе работы." << endl;

    testPause();

    cout << "Создадим пустой документ" << endl;
    Document doc1;
    cout << doc1;

    testPause();

    cout << "Изменим свойства пустого документа:" << endl
        << "Название: Спецификация по чертежу 52" << endl
        << "Тип: Стандарт" << endl
        << "Размер: 5732 байта" << endl
        << "Путь в ФС: /Альянс/Чертежи/52/Спецификация.xls" << endl
        << "Автор: Борисов Петр (разработчик)" << endl
        << "Дата создания: 24 мая 2014 года" << endl;
    doc1.setTitle("Спецификация по чертежу 52");
    doc1.setType(Standart);
    doc1.setSize(5732);
    doc1.setPath("/Альянс/Чертежи/52/Спецификация.xls");
    doc1.setAuthor(DocumentAuthor("Борисов Петр", "Разработчик"));
    doc1.setCreatedDate("2014-05-24");
    cout << doc1;

    testPause();

    cout << "Изменим свойства: редактор, дата редактирования." << endl;
    doc1.setEditor(DocumentAuthor("Матвеев Алексей", "Руководитель"));
    doc1.setEditedDate(false);

    cout << doc1;

    testPause();

    cout << "Получим все свойства документа:" << endl
        << "Название: " << doc1.getTitle() << endl
        << "Тип: " << doc1.getType(true) << endl
        << "Размер: " << doc1.getSize() << endl
        << "Путь в ФС: " << doc1.getPath() << endl
        << "Автор: " << doc1.getAuthor() << endl
        << "Дата создания: " << doc1.getCreatedDate() << endl
        << "Редактор: " << doc1.getEditor() << endl
        << "Дата редактирования: " << doc1.getEditedDate() << endl;
}
void functionTest8() {
    cout << "Работники организации имеют дело с большим количеством документов. \nПоэтому их удобно разделить по типам." << endl;

    testPause();

    cout << "Создадим документ каждого возможного типа и добавим их в одну папку." << endl;

    Document
        doc1("Приказ Альянс", Order),
        doc2("Протокол Альянс", Protocol),
        doc3("Решение Альянс", Decision),
        doc4("Договор Альянс", Contract),
        doc5("Письмо Альянс", Letter),
        doc6("Справка Альянс", Certificate),
        doc7("Счет Альянс", Bill),
        doc8("Стандарт Альянс", Standart),
        doc9("Закон Альянс", Law),
        doc10("Статья Альянс", Article),
        doc11("Книга Альянс", Book),
        doc12("Карта Альянс", Map),
        doc13("Архив Альянс", Archive),
        doc14("Фото Альянс", Other);
    cout << doc1 << doc2 << doc3 << doc4 << doc5 << doc6 << doc7 << doc8 << doc9 << doc10 << doc11 << doc12 << doc13 << doc14;

    testPause();

    DocumentFolder folder1("Проект Альянс", DocumentAuthor("Матвеев Алексей", "Руководитель"));
    folder1.add(doc1);
    folder1.add(doc2);
    folder1.add(doc3);
    folder1.add(doc4);
    folder1.add(doc5);
    folder1.add(doc6);
    folder1.add(doc7);
    folder1.add(doc8);
    folder1.add(doc9);
    folder1.add(doc10);
    folder1.add(doc11);
    folder1.add(doc12);
    folder1.add(doc13);
    folder1.add(doc14);

    cout << folder1;
}
void functionTest9() {
    cout << "В процессе работы удобно создавать одни объекты на основе других." << endl;

    testPause();

    cout << "Создадим следующие объекты: документ, папка, дата, автор" << endl;
    DocumentEditor editor1("Васильева Александра", "Бухгалтер");
    Document doc1("Счет Пилот январь 2015", Bill, 37, "/Счета/2015/январь/Пилот.xls", "2015-02-01", editor1);
    DocumentFolder folder1("Проект Пилот", DocumentAuthor("Матвеев Алексей", "Руководитель"));
    folder1.add(doc1);
    DocumentDate date1("2016-12-25");
    cout << doc1 << folder1 << endl << date1 << endl << editor1;

    testPause();

    cout << "Создадим пустые объекты тех же типов" << endl;
    DocumentEditor editor2;
    Document doc2;
    DocumentFolder folder2;
    DocumentDate date2;
    cout << doc2 << folder2 << endl << date2 << endl << editor2;

    testPause();

    cout << "С помощью операторов присваивания скопируем первые объекты во вторые." << endl;

    doc2 = doc1;
    folder2 = folder1;
    date2 = date1;
    editor2 = editor1;
    
    cout << doc2 << folder2 << endl << date2 << endl << editor2;
}
void functionTest10() {
    cout << "Кроме хранения информации о документах, необходим удобный способ просмотра этой информации." << endl;

    testPause();

    cout << "Создадим документ со всеми полями и распечатаем его" << endl;
    Document doc1("Закон о защите прав потребитилей", Law, 3945, "/Законы/Потребитель.doc", "2015-02-18", DocumentAuthor("Большаков Иван", "Юрист"));
    doc1.setEditor(DocumentEditor("Матвеев Алексей", "Руководитель"));
    doc1.setEditedDate("2015-03-01");
    cout << doc1;
}
void functionTest11() {
    cout << "Для хранения документов используются папки. Папки также обладают свойствами, которые могут со временем меняться." << endl;
    
    testPause();

    cout << "Создадим папку, укажем все ее свойства, добавим в нее документы и распечатаем." << endl;
    DocumentFolder folder1("Навигация Москвы", DocumentAuthor("Большаков Иван", "Разработчик"));
    folder1.setEditor(DocumentEditor("Матвеев Алексей", "Руководитель"));
    Document doc1("Письмо Президенту", Letter);
    Document doc2("Москва", Map, 4500, "/Карты России/МОСКВА.jpg");
    folder1.add(doc1);
    folder1.add(doc2);
    cout << doc1 << doc2 << folder1;
}
void functionTest12() {
    cout << "Для просмотра списка документов в папке удобно представлять структуру папки в виде списка. \nКогда документов в папке много, удобно разделять документы по типам." << endl;

    testPause();

    cout << "Создадим папку, заполним ее документами разных типов и распечатаем" << endl;
    DocumentFolder folder1("Проект Контур", DocumentAuthor("Матвеев Алексей", "Руководитель"));
    for(int i = 0; i < Folder; i++) {
        for(int j = 0; j < (i+2)/2; j++) {
            char letter[2] = { (char) (65+j), '\0'};
            const char *name = concatCharStrings(getDocumentTypeName((BasicDocumentType) i), " ", letter);
            Document doc(name, (BasicDocumentType) i, i*101+j);
            folder1.add(doc);
            delete[] name;
        }
    }
    folder1.list(cout);
    
    testPause();

    cout << "Распечатаем папку документов по типам" << endl;
    folder1.listByTypes(cout);
}
void functionTest13() {
    cout << "Каждое свойство папки может изменяться в процессе работы." << endl;

    testPause();

    cout << "Создадим пустую папку" << endl;
    DocumentFolder folder1;
    cout << folder1;

    testPause();

    cout << "Изменим свойства папки:" << endl
        << "Название: Проект Лемниската" << endl
        << "Автор: Матвеев Алексей (руководитель)" << endl
        << "Редактор: Васильева Александра (бухгалтер)" << endl;
    folder1.setTitle("Проект Лемниската");
    folder1.setAuthor(DocumentAuthor("Матвеев Алексей", "Руководитель"));
    folder1.setEditor(DocumentEditor("Васильева Александра", "Бухгалтер"));
    cout << folder1;

    testPause();

    cout << "Добавим документ в папку и изменим таким образом свойство количество документов в папке" << endl;
    Document doc1("Счет Лемниската апрель-июнь 2015", Bill);
    folder1.add(doc1);
    cout << folder1;

    testPause();

    cout << "Получим и распечатаем информацию о папке" << endl;
    cout << "Название: " << folder1.getTitle() << endl
        << "Автор: " << folder1.getAuthor() << endl
        << "Редактор: " << folder1.getEditor() << endl
        << "Кол-во документов в папке: " << folder1.size() << endl;
}
void functionTest14() {
    cout << "Основные операции, которые проводятся над папкой сотрудниками, - добавление в папку и удаление документов из папки." << endl;

    testPause();

    cout << "Создадим папку, не добавляя в нее документов." << endl;
    DocumentFolder folder1("Проект Инфинитив", DocumentAuthor("Большаков Иван", "Разработчик"));
    folder1.setEditor(DocumentEditor("Матвеев Алексей", "Руководитель"));
    cout << folder1;

    testPause();

    cout << "Добавим три документа в папку" << endl;
    Document
        doc1("Справка Инфинитив", Certificate, 345, "/Справки/Инфинитив/Скан.jpg"),
        doc2("Приказ Инфинитив", Order, 872, "/Приказы/Инифинитив/Скан.pdf"),
        doc3("Договор Инфинитив 1", Contract, 1500, "/Договора/Инифинитив/1.doc");
    cout << doc1 << doc2 << doc3;

    folder1.add(doc1);
    folder1.add(doc2);
    folder1.add(doc3);
    cout << folder1;

    testPause();

    cout << "Удалим документ с индексом 0" << endl;
    folder1.remove(0);
    cout << folder1;

    testPause();

    cout << "Получим документ с названием Справка Инфинитив и удалим его" << endl;
    Document *doc = (Document*) folder1["Справка Инфинитив"];
    if(doc != NULL) {
        cout << *doc;
        folder1.remove(doc);
    }
    cout << folder1;
}
void functionTest15() {
    cout << "Важной операцией является слияние папок - создание новой папки, включая документы из двух папок." << endl;

    testPause();

    cout << "Создадим две папки, добавим в каждую из них несколько документов" << endl;
    DocumentFolder
        folder1("Проект Профи1"),
        folder2("Проект Профи2");

    Document
        doc1("Договор Профи", Contract, 1987, "/Профи/Договор.pdf", "2015-01-01"),
        doc2("Договор Профи старый", Contract, 1902.5, "/Профи/Договор_старый.pdf", "2014-12-02"),
        doc3("Счет сентябрь 2014", Bill, 160, "/Профи/Счет_2014-09.doc", "2014-09-02"),
        doc4("Счет октябрь 2014", Bill, 172, "/Профи/Счет_2014-10.doc", "2014-10-06"),
        doc5("ГОСТ 17474-80", Standart, 17006, "/Документация/ГОСТ 17474-80.pdf", "2015-01-02"),
        doc6("Реклама газета", Article, 1900, "/СМИ/Газета_Профи.pdf", "2015-02-07");
    folder1.add(doc1);
    folder2.add(doc2);
    folder1.add(doc3);
    folder2.add(doc4);
    folder2.add(doc5);
    folder2.add(doc6);

    cout << folder1;
    cout << folder2;

    testPause();

    cout << "Сольем эти две папки и распечатаем получившуюся папку, а также убедимся в том, что две другие папки не изменились." << endl;
    cout << (folder1 + folder2) << folder1 << folder2;

}
void functionTest16() {
    cout << "Возможна ситуация, когда сотрудникам необходимо создать новую папку на основе другой и добавить всего один новый документ." << endl;

    testPause();

    cout << "Создадим новую папку" << endl;
    DocumentFolder
        folder1("Проект Альфа");

    Document
        doc1("Договор Альфа", Contract, 1987, "/Альфа/Договор.pdf", "2015-01-01"),
        doc2("Счет Альфа январь 2015", Bill, 1900, "/Счета/2015/январь/Альфа.pdf", "2015-01-31");

    folder1.add(doc1);
    folder1.add(doc2);
    cout << folder1;

    testPause();

    cout << "Создадим новый документ" << endl;
    Document doc3("Договор Альфа-Партнер", Contract, 1567, "/Альфа-Партнер/Договор.pdf", "2016-01-01");
    cout << doc3;

    testPause();

    cout << "Создадим новую папку на основе старой и добавим в нее сразу новый документ, \nраспечатаем получившуюся папку и убедимся, что старая папка осталась без изменений." << endl;
    cout << (folder1 + doc3) << folder1;
}
void functionTest17() {
    cout << "Возможна ситуация, когда необходимо удалить из папки документы, которые уже есть в другой папке" << endl;

    testPause();

    cout << "Создадим две папки, в которых есть одинаковые документы (но не все)" << endl;
    DocumentFolder folder1("Проект Зоопарк1"),
        folder2("Проект Зоопарк2");

    Document doc1("Договор Зоо", Contract),
        doc2("Счет Зоо май 2015", Bill),
        doc3("Договор партнерства 2014-2016", Contract),
        doc4("Рекламная статья 1", Article),
        doc5("Приказ сотрудникам Зоо", Order);
    folder1.add(doc1);
    folder2.add(doc1);
    folder1.add(doc2);
    folder2.add(doc2);
    folder1.add(doc4);
    folder2.add(doc3);
    folder1.add(doc5);
    folder2.add(doc5);

    cout << folder1 << folder2;

    testPause();

    cout << "Получим новую папку, в которой есть все документы из первой папки, но которых нет во второй" << endl
        << "Убедимся, что изначальные папки остались без изменений." << endl;
    cout << (folder1 - folder2) << folder1 << folder2;
}
void functionTest18() {
    cout << "Возможна ситуация, когда сотрудникам необходимо создать новую папку, в которой нет одного документа из другой папки." << endl;

    testPause();

    cout << "Создадим папку, заполним ее документами" << endl;
    DocumentFolder folder1("Корпоратив 2015");
    Document doc1("Меню корп2015", Bill),
        doc2("Список сотрудников", Other),
        doc3("Приказ выходные", Order),
        doc4("Презентация и фото", Archive);
    folder1.add(doc1);
    folder1.add(doc2);
    folder1.add(doc3);
    folder1.add(doc4);
    cout << folder1;

    testPause();

    cout << "Получим документ с названием Меню корп2015" << endl;
    Document *d = (Document*) folder1["Меню корп2015"];
    cout << *d;

    testPause();

    cout << "Создадим новую папку на основе старой без документ Меню корп2015." << endl
        << "Убедимся, что старая папка осталась без изменений." << endl;
    cout << (folder1 - *d) << folder1;
}
