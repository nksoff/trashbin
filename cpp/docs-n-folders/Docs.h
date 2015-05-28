#include <iostream>
#include <string>
#include <ctime>
#include <stdarg.h>
#include <iomanip>
#include <typeinfo>

using namespace std;

/**
 * Файл Docs.h - содержит все необходимые прототипы
 * классов и методов для системы классов документов и папок
 *
 * Автор: Слимов Никита: ИУ5-23
 * Дата разработки: апрель-июнь 2015
 */

namespace doc {
#ifndef _DOCS_H
#define _DOCS_H

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
    #define IS_WIN 1
    #define USE_SAFE_FUNCTIONS 1
#endif
    
    /**
     * -------------------------------------------------------------------
     * Базовые функции
     */
    // strcpy / strcpy_s
    inline void strcpy(char *to, int length, const char *from) {
        #ifdef USE_SAFE_FUNCTIONS
        strcpy_s(to, length, from);
        #else
        ::strcpy(to, from);
        #endif
    }
    // strcat / strcat_s
    inline void strcat(char *to, int length, const char *from) {
        #ifdef USE_SAFE_FUNCTIONS
        strcat_s(to, length, from);
        #else
        ::strcat(to, from);
        #endif
    }

    // конкатерация двух (или трех) строк
    const char *concatCharStrings(const char*, const char*, const char* = NULL);
    // выделение памяти под строку и копирование в нее исходной
    char *copyCharString(const char*);
    // копирование списка
    template<class T>
    T* copyList(T*, int);

    // возвращает исходную строку, если она не пустая или строку из второго аргумента, если исходная пустая
    const char *showOrDefault(const char*, const char* = "[не указано]");
    // структура для хранения специальных символов, которые нужно вывести
    struct _smanip;
    // перегрузка оператора вывода структуры для правильного вывода специальных символов
    ostream& operator <<(ostream&, const _smanip&);
    // создание структуры для вывода специальных символов
    const _smanip s(int, ...);
    // манипулятор начала вывода информации об объекте
    ostream& showStart(ostream&);
    // манипулятор выывода следующей строки информации об объекте
    ostream& showNL(ostream&);
    // манипулятор окончания вывода информации об объекте
    ostream& showEnd(ostream&);

    /**
     * -------------------------------------------------------------------
     * Класс OrdinaryObject - абстрактный - обыкновенный объект
     * Содержит поле названия объекта, методы для получения и задания этого поля
     * Перегружены операторы сравнения и оператор вывода в поток
     */
    class OrdinaryObject {
    public:
        virtual ~OrdinaryObject() {
            if(_title)
                delete[] _title;
        }

        // задание поля названия объекта
        void setTitle(const char *title) {
            _title = copyCharString(title);
        }
        void setName(const char *title) {
            return setTitle(title);
        }
        // получение названия объекта
        const char *getTitle() const {
            return _title;
        }
        const char *getName() const {
            return getTitle();
        }
        // проверка равенства объектов
        virtual bool equal(const OrdinaryObject&) const = 0;
        // вывод информации об объекте
        virtual void show(bool full = false, ostream &stream = cout) const = 0;
        // оператор вывода в поток
        friend ostream& operator << (ostream &stream, const OrdinaryObject &obj) {
            obj.show(true, stream);
            return stream;
        }
        // операторы сравнения
        bool operator < (OrdinaryObject &obj) {
            return strcmp(_title, obj._title) < 0;
        }
        bool operator > (OrdinaryObject &obj) {
            return strcmp(_title, obj._title) > 0;
        }
        bool operator == (OrdinaryObject &obj) {
            return (this == &obj) || equal(obj);
        }
        bool operator != (OrdinaryObject &obj) {
            return !(*this == obj);
        }

    protected:
        // защищенный конструктор (название)
        OrdinaryObject(const char *title = "") : _title(NULL) {
            _title = copyCharString(title);
        }
        // имя/название объекта
        char *_title;
    };

    /**
     * -------------------------------------------------------------------
     * Перечисление типов документов
     */
    enum BasicDocumentType {
        Order, // приказ
        Protocol, // протокол
        Decision, // решение
        Contract, // договор
        Letter, // письмо
        Certificate, // справка
        Bill, // счет
        Standart, // стандарт.норма
        Law, // закон

        Article, // статья
        Book, // книга
        Map, // карта

        Archive, // архив
        
        Other, // другой документ

        Folder, // папка
    };
    // получение строки, содержащей название типа документа
    const char* getDocumentTypeName(BasicDocumentType);
    // получение типа документа по строке, содержащей его название
    BasicDocumentType getDocumentTypeByName(const char*);

    /**
     * -------------------------------------------------------------------
     * Класс BasicDocumentObject - абстрактный - базовый класс документа
     * Включает в себя методы для получения и задания типа документа
     * Содержит метод клонирования объекта
     */
    class BasicDocumentObject : public OrdinaryObject {
    public:
        virtual ~BasicDocumentObject() {}

        // получение типа документа
        BasicDocumentType getType() const;
        // получение строки, содержащей название типа документа
        const char *getType(bool val) const;
        // задание типа документа
        void setType(BasicDocumentType type);
        // задание типа документа
        void setType(const char *type);
        // проверка равенства объектов
        virtual bool equal(const OrdinaryObject&) const = 0;
        // метод клонирования объекта
        virtual BasicDocumentObject *clone() const = 0;
        // метод вывода информации об объекте
        virtual void show(bool full = false, ostream &stream = cout) const = 0;
    protected:
        // защищенный конструктор (название, тип)
        BasicDocumentObject(const char* = "", BasicDocumentType = Other);
        // тип документа
        BasicDocumentType _type;
    };

    /**
     * -------------------------------------------------------------------
     * Класс DocumentDate - дата и время изменения/создания документа
     * Содержит методы вывода и получения даты в заданом формате
     * Перегружены операторы сравнения и вывода в поток
     */
    class DocumentDate {
    public:
        // конструктор без параметров - пустая дата
        DocumentDate();
        // конструктор (true = дата и время не указаны, false = текущие дата и время)
        DocumentDate(bool);
        // конструктор (дата в формате ГГГГ-ММ-ДД или ГГГГ-ММ-ДД ЧЧ:ММ:СС)
        DocumentDate(const char*);
        // конструтор (time_t)
        DocumentDate(time_t val);
        // конструктор копирования
        DocumentDate(const DocumentDate &date);

        // получение даты в виде строки
        const char *format(const char* = DEFAULT_FORMAT, int = 50) const;
        // вывод информации об объекте
        void show(const char * = DEFAULT_FORMAT, ostream& = cout) const;
        // проверка, указана дата или нет
        bool isEmpty() const;
        // операторы сравнения дат
        bool operator > (DocumentDate&);
        bool operator < (DocumentDate&);
        bool operator == (DocumentDate&);
        // оператор присваивания
        DocumentDate& operator = (const DocumentDate&);
        // оператор присваивания
        DocumentDate& operator = (const char *);
        // оператор вывода в поток
        friend ostream& operator <<(ostream&, const DocumentDate&);
    protected:
        // значение даты в виде числа секунд (time_t)
        time_t _val;
        // флаг, указывающий на то, что дата пуста (нет данных)
        bool _empty;

        // формат вывода даты по умолчанию
        static const char *DEFAULT_FORMAT;
    };

    /**
     * -------------------------------------------------------------------
     * Класс DocumentEditor - создатель(автор)/редактор документа
     * Содержит методы получения и задания должности, проверки равенства объектов
     */
    class DocumentEditor : public OrdinaryObject {
    public:
        // конструктор (имя, должность)
        DocumentEditor(const char* = "", const char* = "");
        // конструктор копирования
        DocumentEditor(const DocumentEditor &editor);
        virtual ~DocumentEditor();
        // получение должности
        const char *getPosition() const;
        // изменение должности
        void setPosition(const char *position);
        // проверка, пустой объект или нет
        bool isEmpty() const;
        // проверка равенства объектов
        virtual bool equal(const OrdinaryObject&) const;
        // вывод информации об объекте
        virtual void show(bool = false, ostream& = cout) const;
        // оператор присваивания
        DocumentEditor& operator = (const DocumentEditor&);
    protected:
        // должность
        char *_position;
    };
    // DocumentAuthor = DocumentEditor
    typedef DocumentEditor DocumentAuthor;
    
    /**
     * -------------------------------------------------------------------
     * Класс Document - класс документа
     * Содержит методы для получения и изменения размера файла,
     * пути в файловой системе, автора и редактора документа,
     * даты изменения и даты создания документа,
     * для клонирования объекта, проверки равенства объектов,
     * вывода инфорамции об объекте
     */
    class Document : public BasicDocumentObject {
    public:
        // конструктор (название, тип, размер, путь в ФС, дата создания, автор)
        Document(const char* = "", BasicDocumentType = Other, double = 0, const char* = "", DocumentDate = "", DocumentAuthor = "");
        // конструктор копирования
        Document(const Document&);
        virtual ~Document();

        // получение размера
        double getSize() const;
        // изменение размера
        void setSize(double);

        // получение пути в ФС
        const char *getPath() const;
        // изменение пути в ФС
        void setPath(const char*);

        // получение автора
        const DocumentAuthor getAuthor() const;
        // изменение автора
        void setAuthor(DocumentAuthor);

        // получение редактора
        const DocumentEditor getEditor() const;
        // изменение редактора
        void setEditor(DocumentEditor);

        // получение даты создания
        const DocumentDate getCreatedDate() const;
        // изменение даты создания
        void setCreatedDate(DocumentDate);
        // получение даты изменения
        const DocumentDate getEditedDate() const;
        // изменение даты измнения
        void setEditedDate(DocumentDate);

        // редактирование документа (задание даты изменения и редактора)
        void edit(DocumentDate, DocumentEditor);
        // редактирование документа (задание редактора и даты изменения)
        void edit(DocumentEditor, DocumentDate);

        // клонирование объекта
        virtual BasicDocumentObject *clone() const;
        // проверка равества объектов
        virtual bool equal(const OrdinaryObject&) const;
        // вывод информации об объекте
        virtual void show(bool = false, ostream& = cout) const;
        // оператор присваивания
        Document& operator =(const Document&);
    protected:
        // размер
        double _size;
        // путь в ФС
        char *_path;
        // автор
        DocumentAuthor _author;
        // редактор
        DocumentEditor _editor;

        // дата создания
        DocumentDate _createdDate;
        // дата изменения
        DocumentDate _editedDate;
    };
    /**
     * -------------------------------------------------------------------
     * Класс BasicDocumentFolder - абстрактный - базовый класс папки
     * Содержит методы для добавления, удаления элементов папки,
     * получения кол-ва элементов в папке, очистки папки,
     * получения списка элементов папки отдельного типа,
     * вывода информации о папке и списка ее элементов,
     * сравнения двух папок.
     * Перегружен оператор индексирования
     */
    class BasicDocumentFolder : public BasicDocumentObject {
    public:
        virtual ~BasicDocumentFolder();

        // добавление элемента в папку (указатель)
        void add(const BasicDocumentObject*);
        // добавление элемента в папку (ссылка)
        void add(const BasicDocumentObject&);
        // добавление элемента в папку (массив указателей на элементы, длина массива)
        void add(const BasicDocumentObject**, int);

        // удаление элемента из папки (индекс)
        void remove(int);
        // удаление элемента из папки (указатель)
        void remove(const BasicDocumentObject*);
        // удаление элемента из папки (ссылка)
        void remove(const BasicDocumentObject&);
        // очистка папки
        void clear();

        // получение количества элементов в папке
        int length() const;
        // получение количества элементов в папке
        int size() const;

        // получение определенного элемента папки (индекс)
        BasicDocumentObject *get(int) const;
        // получение всех документов папки
        BasicDocumentObject **getDocuments(int&) const;
        // получение элементов папки определенного типа
        BasicDocumentObject **getDocuments(const BasicDocumentType, int&) const;
        // получение подпапок папки
        BasicDocumentObject **getFolders(int&) const;
        // получение всех элементов папки
        BasicDocumentObject **getAll(int&) const;

        // подсчет количества элементов определенного типа в папке
        int countDocuments(BasicDocumentType) const;

        // вывод списка элементов папки
        void list(ostream& = cout, BasicDocumentObject** = NULL, int = 0) const;
        // вывод списка элементов папки, разделенным по типам
        void listByTypes(ostream& = cout) const;

        // оператор индексирования (индекс)
        BasicDocumentObject *operator[](int);
        // оператор индексирования (название)
        BasicDocumentObject *operator[](const char *);
        // оператор индексирования (тип)
        BasicDocumentObject **operator[](const BasicDocumentType);

        // клонирование объекта
        virtual BasicDocumentObject *clone() const = 0;
        // проверка равенства объектов
        virtual bool equal(const OrdinaryObject&) const = 0;
        // вывод информации об объекте
        virtual void show(bool full = false, ostream &stream = cout) const = 0;
    protected:
        // защищенный конструктор (название, массив элементов, размер массива)
        BasicDocumentFolder(const char* = "", const BasicDocumentObject** = NULL, int = 0);
        
        // начальный размер массива
        const int INITIAL_SIZE;

        // массив, хранящий указатели на элементы папки
        BasicDocumentObject **_children;
        // текущее кол-во элементов в папке
        int _count;
        // выделенное количество памяти для элеентов папки
        int _maxCount;

        // динамическое выделение памяти при нехватке
        void _reinitMemory();
        // сортировка папки
        void _sort();
    };

    
    /**
     * -------------------------------------------------------------------
     * Класс DocumentFolder
     * Содержит методы для получения и изменения создателя папки, последнего редактора папки,
     * проверки равенства объектов, вывода информации о папке.
     * Перегружены опреаторы сложения, вычитания, +=, -=
     */
    class DocumentFolder : public BasicDocumentFolder {
    public:
        // конструктор (название, автор, массив элементов, длина массива)
        DocumentFolder(const char* = "", DocumentAuthor = "", const BasicDocumentObject** = NULL, int = 0);
        // конструктор копирования
        DocumentFolder(const DocumentFolder&);
        virtual ~DocumentFolder();

        // получение автора
        const DocumentAuthor getAuthor() const;
        // изменение автора
        void setAuthor(DocumentAuthor);

        // получение редактора
        const DocumentEditor getEditor() const;
        // изменение редактора
        void setEditor(DocumentEditor);

        // изменение редактора
        void edit(DocumentEditor);

        // клонирование объекта
        virtual BasicDocumentObject *clone() const;
        // проверка равенства объектов
        virtual bool equal(const OrdinaryObject&) const;
        // вывод информации об объекте
        virtual void show(bool = false, ostream& = cout) const;

        // оператор присваивания
        DocumentFolder& operator =(const DocumentFolder&);

        // оператор сложения папки и документа
        DocumentFolder operator +(const Document&);
        // оператор сложения папки и папки
        DocumentFolder operator +(const DocumentFolder&);
        // оператор вычитания документа из папки
        DocumentFolder operator -(const Document&);
        // оператор вычитания папки из папки
        DocumentFolder operator -(const DocumentFolder&);
        
        // оператор присваивания сложения элемента папки
        DocumentFolder& operator +=(const BasicDocumentObject&);
        // оператор присваивания вычитания элемента папки
        DocumentFolder& operator -=(const BasicDocumentObject&);
        
        // оператора сложения документа и папки
        friend DocumentFolder operator + (Document&, DocumentFolder&);

    protected:
        // автор папки
        DocumentAuthor _author;
        // редактор папки
        DocumentEditor _editor;
    };
#endif
};