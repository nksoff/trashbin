#include "Docs.h"

/**
 * Файл Docs.cpp - содержит все необходимые описания
 * классов и методов для системы классов документов и папок
 *
 * Автор: Слимов Никита: ИУ5-23
 * Дата разработки: апрель-июнь 2015
 */

namespace doc {
    /**
     * -------------------------------------------------------------------
     * Базовые функции
     */
    // конкатерация двух (или трех) строк
    const char *concatCharStrings(const char *str1, const char *str2, const char *str3) {
        int length = strlen(str1) + strlen(str2) + 1;
        if(str3 != NULL) length += strlen(str3);
        char *to = new char[length];
        strcpy(to, length, str1);
        strcat(to, length, str2);
        if(str3 != NULL) {
            strcat(to, length, str3);
        }
        return to;
    }
    
    // выделение памяти под строку и копирование в нее исходной
    char *copyCharString(const char *from) {
        int length = strlen(from) + 1;
        char *to = new char[length];
        strcpy(to, length, from);
        return to;
    }

    // копирование списка
    template<class T>
    T* copyList(T *from, int count) {
        T *list = new T[count];
        for(int i = 0; i < count; i++) {
            list[i] = from[i];
        }
        return list;
    }

    // возвращает исходную строку, если она не пустая или строку из второго аргумента, если исходная пустая
    const char *showOrDefault(const char *what, const char *standart) {
        return (what == NULL || strlen(what) == 0 ? standart : what);
    }

    // структура для хранения специальных символов, которые нужно вывести
    struct _smanip {
    public:
        // конструктор (массив кодов символов, их количество)
        _smanip(int *arg, int count = 1) :_arg(arg), _count(count) {}
        ~_smanip() {
            if(_arg) delete[] _arg;
        }
        // массив кодов символа
        int *_arg;
        // кол-во чисел в массиве
        int _count;
    };

    // перегрузка оператора вывода структуры для правильного вывода специальных символов
    ostream& operator <<(ostream &stream, const _smanip &m) {
        #ifdef IS_WIN
        system("chcp 866 > nul");
        #endif
        for(int i = 0; i < m._count; i++) {
            if(m._arg[i] == 0) continue;
            #ifdef IS_WIN
            stream << (unsigned char) m._arg[i];
            #else
            switch(m._arg[i]) {
                case 192: stream << "└"; break;
                case 194: stream << "├"; break;
                case 195: stream << "├"; break;
                case 196: stream << "─"; break;
            }
            #endif
        }
        #ifdef IS_WIN
        system("chcp 1251 > nul");
        #endif
        return stream;
    }

    // создание структуры для вывода специальных символов
    const _smanip s(int count, ...) {
        va_list args;
        va_start(args, count);
        int *nums = new int[count];
        for(int i = 0; i < count; i++) {
            nums[i] = va_arg(args, int);
        }
        va_end(args);

        return _smanip(nums, count);
    }

    // манипулятор начала вывода информации об объекте
    ostream& showStart(ostream &stream) {
        stream << endl << s(1, 195) << "------- ";
        return stream;
    }
    // манипулятор выывода следующей строки информации об объекте
    ostream& showNL(ostream &stream) {
        stream << endl << "|   ";
        return stream;
    }
    // манипулятор окончания вывода информации об объекте
    ostream& showEnd(ostream &stream) {
        stream << endl << s(1, 192) << "-------------" << endl;
        return stream;
    }

    /**
     * -------------------------------------------------------------------
     * BasicDocumentType
     */
     const char *_documentTypesNames[] = {
        "Приказ",
        "Протокол",
        "Решение",
        "Договор",
        "Письмо",
        "Сертификат",
        "Счет",
        "Стандарт",
        "Закон",

        "Статья",
        "Книга",
        "Карта",

        "Архив",

        "Другой документ",

        "Папка"
    };
    const int _documentTypesNamesCount = sizeof(_documentTypesNames) / sizeof(char*);
    // получение строки, содержащей название типа документа
    const char* getDocumentTypeName(BasicDocumentType type) {
        return _documentTypesNames[type];
    }
    
    // получение типа документа по строке, содержащей его название
    BasicDocumentType getDocumentTypeByName(const char *name) {
        for(int i = 0; i < _documentTypesNamesCount; i++) {
            if(strcmp(name, _documentTypesNames[i]) == 0) {
                return (BasicDocumentType) i;
            }
        }
        return Other;
    }

    /**
     * -------------------------------------------------------------------
     * BasicDocumentObject
     */
    // защищенный конструктор (название, тип)
     BasicDocumentObject::BasicDocumentObject(const char *title, BasicDocumentType type) :
     OrdinaryObject(title), _type(type) {}

    // получение типа документа
     BasicDocumentType BasicDocumentObject::getType() const {
        return _type;
    }
    // получение строки, содержащей название типа документа
    const char *BasicDocumentObject::getType(bool val) const {
        return getDocumentTypeName(_type);
    }
    // задание типа документа
    void BasicDocumentObject::setType(BasicDocumentType type) {
        _type = type;
    }
    // задание типа документа
    void BasicDocumentObject::setType(const char *type) {
        _type = getDocumentTypeByName(type);
    }


    /**
     * -------------------------------------------------------------------
     * DocumentDate
     */
    // формат вывода даты по умолчанию
     const char *DocumentDate::DEFAULT_FORMAT = "%Y-%m-%d %H:%M:%S";
    // конструктор без параметров - пустая дата
     DocumentDate::DocumentDate() : _empty(true) {
     }
    // конструктор (true = дата и время не указаны, false = текущие дата и время)
     DocumentDate::DocumentDate(bool empty) : _empty(empty) {
        if(!empty) {
            _val = time(NULL);
        }
    }
    // конструктор (дата в формате ГГГГ-ММ-ДД или ГГГГ-ММ-ДД ЧЧ:ММ:СС)
    DocumentDate::DocumentDate(const char *date) : _empty(false) {
        *this = date;
    }
    // конструтор (time_t)
    DocumentDate::DocumentDate(time_t val) : _empty(false) {
        _val = val;
    }
    // конструктор копирования
    DocumentDate::DocumentDate(const DocumentDate &date) : _empty(false) {
        *this = date;
    }
    
    // получение даты в виде строки
    const char *DocumentDate::format(const char *format, int length) const {
        if(format == NULL) format = DEFAULT_FORMAT;
        #ifdef USE_SAFE_FUNCTIONS
        tm t, *tinfo = &t;
        localtime_s(tinfo, &_val);
        #else
        tm *tinfo = localtime(&_val);
        #endif
        
        char *res = new char[length+1];
        strftime(res, length, format, tinfo);
        return res;
    }
    // вывод информации об объекте
    void DocumentDate::show(const char *form, ostream &stream) const {
        if(form == NULL) form = DEFAULT_FORMAT;
        if(!_empty) {
            const char *output = format(form, 50);
            stream << output;
            delete[] output;
        }
        else
            stream << "[дата не указана]";
    }

    // проверка, указана дата или нет
    bool DocumentDate::isEmpty() const {
        return _empty;
    }

    // оператора сравнение >
    bool DocumentDate::operator > (DocumentDate &date) {
        return _val > date._val;
    }
    // оператор сравнения <
    bool DocumentDate::operator < (DocumentDate &date) {
        return _val < date._val;
    }
    // оператора сравнения ==
    bool DocumentDate::operator == (DocumentDate &date) {
        return _val == date._val;
    }
    // оператор присваивания
    DocumentDate& DocumentDate::operator = (const DocumentDate &date) {
        if(&date == this) return *this;
        _val = date._val;
        _empty = date._empty;
        return *this;
    }
    // оператор присваивания (строка с датой ГГГГ-ММ-ДД или ГГГГ-ММ-ДД ЧЧ:ММ:СС)
    DocumentDate& DocumentDate::operator = (const char *date) {
        int year, month, day, hour = 0, minute = 0, second = 0;
        switch(strlen(date)) {
            case 10:
            #ifdef USE_SAFE_FUNCTIONS
            sscanf_s(date, "%d-%d-%d", &year, &month, &day);
            #else
            sscanf(date, "%d-%d-%d", &year, &month, &day);
            #endif
            break;
            case 19:
            #ifdef USE_SAFE_FUNCTIONS
            sscanf_s(date, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            #else
            sscanf(date, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            #endif
            break;
            default:
            _empty = true;
            return *this;
            break;
        }

        _empty = false;
        tm time;
        time.tm_year = year - 1900;
        time.tm_mon = month - 1;
        time.tm_mday = day;
        time.tm_hour = hour;
        time.tm_min = minute;
        time.tm_sec = second;
        time.tm_isdst = -1;
        _val = mktime(&time);
        return *this;
    }

    // оператор вывода в поток
    ostream& operator <<(ostream &stream, const DocumentDate &date) {
        date.show(NULL, stream);
        return stream;
    }

    /**
     * -------------------------------------------------------------------
     * DocumentEditor
     */
    // конструктор (имя, должность)
     DocumentEditor::DocumentEditor(const char *name, const char *position) :
     OrdinaryObject(name), _position(NULL) {
        _position = copyCharString(position);
    }
    // конструктор копирования
    DocumentEditor::DocumentEditor(const DocumentEditor &editor): _position(NULL) {
        *this = editor;
    }
    DocumentEditor::~DocumentEditor() {
        if(_position)
            delete[] _position;
    }
    // получение должности
    const char *DocumentEditor::getPosition() const {
        return _position;
    }
    // изменение должности
    void DocumentEditor::setPosition(const char *position) {
        if(_position)
            delete[] _position;
        _position = copyCharString(position);
    }
    // проверка, пустой объект или нет
    bool DocumentEditor::isEmpty() const {
        return strcmp(_title, "") == 0 && strcmp(_title, "") == 0;
    }
    // проверка равенства объектов
    bool DocumentEditor::equal(const OrdinaryObject &obj) const {
        if(typeid(*this) == typeid(obj)) {
            DocumentEditor const *real = dynamic_cast<const DocumentEditor *>(&obj);
            return strcmp(_title, real->_title) == 0
            && strcmp(_position, real->_position) == 0;
        }
        return false;
    }
    // вывод информации об объекте
    void DocumentEditor::show(bool full, ostream &stream) const {
        if(full) {
            stream << showStart << "Автор/редактор документа"
            << showNL << "Имя: " << showOrDefault(_title, "[имя не указано]")
            << showNL << "Должность: " << showOrDefault(_position, "[должность не указана]")
            << showEnd;
        }
        else
        {
            stream << showOrDefault(_title, "[имя не указано]")
            << " (" << showOrDefault(_position, "[должность не указана]") << ")";
        }
    }
    
    // оператор присваивания
    DocumentEditor& DocumentEditor::operator = (const DocumentEditor &editor) {
        if(&editor == this) return *this;
        if(_title)
            delete[] _title;
        if(_position)
            delete[] _position;
        _title = copyCharString(editor._title);
        _position = copyCharString(editor._position);
        return *this;
    }

    /**
     * -------------------------------------------------------------------
     * Document
     */
    // конструктор (название, тип, размер, путь в ФС, дата создания, автор)
     Document::Document(const char *title, BasicDocumentType type, double size, const char *path, DocumentDate createdDate, DocumentAuthor author):
     BasicDocumentObject(title, type), _size(size), _path(copyCharString(path)) {
        _createdDate = createdDate;
        _author = author;
    }
    // конструктор копирования
    Document::Document(const Document &doc) : _path(NULL) {
        *this = doc;
    }
    Document::~Document() {
        if(_path)
            delete[] _path;
    }
    
    // получение размера
    double Document::getSize() const {
        return _size;
    }
    // изменение размера
    void Document::setSize(double size) {
        _size = size;
    }

    // получение пути в ФС
    const char *Document::getPath() const {
        return _path;
    }
    // изменение пути в ФС
    void Document::setPath(const char *path) {
        if(_path)
            delete[] _path;
        _path = copyCharString(path);
    }

    // получение автора
    const DocumentAuthor Document::getAuthor() const {
        return _author;
    }
    // изменение автора
    void Document::setAuthor(DocumentAuthor author) {
        _author = author;
    }

    // получение редактора
    const DocumentEditor Document::getEditor() const {
        return _editor;
    }
    // изменение редактора
    void Document::setEditor(DocumentEditor editor) {
        _editor = editor;
    }

    // получение даты создания
    const DocumentDate Document::getCreatedDate() const {
        return _createdDate;
    }
    // изменение даты создания
    void Document::setCreatedDate(DocumentDate date) {
        _createdDate = date;
    }
    // получение даты изменения
    const DocumentDate Document::getEditedDate() const {
        return _editedDate;
    }
    // изменение даты изменения
    void Document::setEditedDate(DocumentDate date) {
        _editedDate = date;
    }
    
    // редактирование документа (задание даты изменения и редактора)
    void Document::edit(DocumentDate date, DocumentEditor editor) {
        setEditedDate(date);
        setEditor(editor);
    }
    
    // редактирование документа (задание редактора и даты изменения)
    void Document::edit(DocumentEditor editor, DocumentDate date) {
        return edit(date, editor);
    }

    // клонирование объекта
    BasicDocumentObject *Document::clone() const {
        Document *newDoc = new Document(*this);
        return newDoc;
    }
    // проверка равенства объектов
    bool Document::equal(const OrdinaryObject &obj) const {
        if(typeid(*this) == typeid(obj)) {
            Document const *real = dynamic_cast<const Document *>(&obj);
            return strcmp(_title, real->_title) == 0
            && strcmp(_path, real->_path) == 0
            && _type == real->_type;
        }
        return false;
    }
    // вывод информации об объекте
    void Document::show(bool full, ostream &stream) const {
        if(full) {
            stream << showStart << "Документ " << showOrDefault(_title, "[название не указано]") << " (тип: " << getType(true) << ")"
            << showNL << "Размер: " << _size << " байтов"
            << showNL << "Путь в ФС: " << showOrDefault(_path)
            << showNL << "Автор документа: "; _author.show(false, stream);
            stream << ", создан: " << _createdDate
            << showNL << "Редактор документа: "; _editor.show(false, stream);
            stream << ", изменен: " << _editedDate
            << showEnd;
        }
        else
        {
            stream << showOrDefault(_title, "[название не указано]") << " /" << getType(true) << "/";
        }
    }

    // оператор присваивания
    Document& Document::operator = (const Document &doc) {
        if(&doc == this) return *this;
        if(_title)
            delete[] _title;
        if(_path)
            delete[] _path;
        _title = copyCharString(doc._title);
        _type = doc._type;
        _size = doc._size;
        _path = copyCharString(doc._path);
        _author = doc._author;
        _createdDate = doc._createdDate;
        _editor = doc._editor;
        _editedDate = doc._editedDate;
        return *this;
    }

    /**
     * -------------------------------------------------------------------
     * BasicDocumentFolder
     */
    // защищенный конструктор (название, массив элементов, размер массива)
     BasicDocumentFolder::BasicDocumentFolder(const char *title, const BasicDocumentObject **documents, int size) :
     BasicDocumentObject(title, Folder), INITIAL_SIZE(10), _children(NULL), _count(0), _maxCount(size) {
        _reinitMemory();
        if(size > 0) add(documents, size);
    }

    BasicDocumentFolder::~BasicDocumentFolder() {
        clear();
        if(_children)
            delete[] _children;
    }
    
    // добавление элемента в папку (указатель)
    void BasicDocumentFolder::add(const BasicDocumentObject *obj) {
        if(_count >= _maxCount) {
            _reinitMemory();
        }
        _children[_count++] = obj->clone();
        _sort();
    }
    
    // добавление элемента в папку (ссылка)
    void BasicDocumentFolder::add(const BasicDocumentObject &obj) {
        return add(&obj);
    }
    
    // добавление элемента в папку (массив указателей на элементы, размер массива)
    void BasicDocumentFolder::add(const BasicDocumentObject **docs, int size) {
        for(int i = 0; i < size; i++) {
            add(docs[i]);
        }
    }
    
    // удаление элемента из папки (индекс)
    void BasicDocumentFolder::remove(int key) {
        if(key < 0 || key > _count - 1) return;

        delete _children[key];
        for(int j = key + 1; j < _count; j++) {
            _children[j-1] = _children[j];
        }
        _count--;
    }
    // удаление элемента из папки (указатель)
    void BasicDocumentFolder::remove(const BasicDocumentObject *obj) {
        for(int i = 0; i < _count; i++) {
            if(_children[i]->equal(*obj)) {
                remove(i);
            }
        }
    }
    // удаление элемента из папки (ссылка)
    void BasicDocumentFolder::remove(const BasicDocumentObject &obj) {
        return remove(&obj);
    }
    // очистка папки
    void BasicDocumentFolder::clear() {
        for(int i = _count - 1; i >= 0; i--) {
            remove(i);
        }
    }
    
    // получение количества элементов в папке
    int BasicDocumentFolder::length() const {
        return _count;
    }
    // получение количества элементов в папке
    int BasicDocumentFolder::size() const {
        return length();
    }
    
    // получение определенного элемента папки (индекс)
    BasicDocumentObject *BasicDocumentFolder::get(int key) const {
        if(key >= 0 && key < _count) {
            return _children[key];
        }
        return NULL;
    }
    // получение всех документов папки
    BasicDocumentObject **BasicDocumentFolder::getDocuments(int &count) const {
        BasicDocumentObject **tmp = new BasicDocumentObject*[_count];
        count = 0;
        for(int i = 0; i < _count; i++) {
            if(_children[i]->getType() != Folder) {
                tmp[count++] = _children[i];
            }
        }
        BasicDocumentObject **list = copyList(tmp, count);
        delete[] tmp;
        return list;
    }
    // получение элементов папки определенного типа
    BasicDocumentObject **BasicDocumentFolder::getDocuments(const BasicDocumentType type, int &count) const {
        BasicDocumentObject **tmp = new BasicDocumentObject*[_count];
        count = 0;
        for(int i = 0; i < _count; i++) {
            if(_children[i]->getType() == type) {
                tmp[count++] = _children[i];
            }
        }
        BasicDocumentObject **list = copyList(tmp, count);
        delete[] tmp;
        return list;
    }
    // получение подпапок папки
    BasicDocumentObject **BasicDocumentFolder::getFolders(int &count) const {
        return getDocuments(Folder, count);
    }
    
    // получение всех элементов папки
    BasicDocumentObject **BasicDocumentFolder::getAll(int &count) const {
        BasicDocumentObject **list = new BasicDocumentObject*[_count];
        count = 0;
        for(int i = 0; i < _count; i++) {
            list[count++] = _children[i];
        }
        return list;
    }
    
    // подсчет количества элементов определенного типа в папке
    int BasicDocumentFolder::countDocuments(BasicDocumentType type) const {
        int count = 0;
        for(int i = 0; i < _count; i++) {
            if(_children[i]->getType() == type) {
                count++;
            }
        }
        return count;
    }
    
    // вывод списка элементов папки
    void BasicDocumentFolder::list(ostream &stream, BasicDocumentObject **docs, int size) const {
        static int listingLevel = 0;
        static bool listingLast[20] = {};
        static int listingFolderNum[20] = {};

        if(docs == NULL) {
            docs = _children;
            size = _count;
        }
        int level = listingLevel;

        stream << s(1, 194);
        if(level == 1) stream << " (" << listingFolderNum[level-1] << ")";
        stream << " " << showOrDefault(_title) << " [" << size << "]" << endl;
        for(int i = 0; i < size; i++) {
            bool isLast = i == size - 1;
            listingLast[level] = isLast;
            listingFolderNum[level] = i;
            for(int j = 0; j < level; j++) {
                stream << (!listingLast[j] ? "|" : " ") << "   ";
            }
            if(_children[i] != NULL) {
                stream << s(5, isLast ? 192 : 195, 196, 196, 196, _children[i]->getType() == Folder ? 0 : 196);
                if(_children[i]->getType() == Folder) {
                    listingLevel = level + 1;
                    dynamic_cast<BasicDocumentFolder*>(_children[i])->list();
                }
                else
                {
                    stream << " ";
                    if(level == 0) stream << "(" << i << ") ";
                    _children[i]->show(false, stream);
                    stream << endl;
                }
            }
        }

        if(level == 0) {
            listingLevel = 0;
        }
    }
    // вывод списка элементов папки, разделенным по типам
    void BasicDocumentFolder::listByTypes(ostream &stream) const {
        static int listingLevel = 0;
        static bool listingLast[20] = {};

        int level = listingLevel;
        int size, last;

        for(int i = Folder; i >= 0; i--) {
            if(countDocuments((BasicDocumentType) i) > 0) {
                last = i;
                break;
            }
        }

        stream << s(1, 194);
        stream << " " << showOrDefault(_title) << " [" << _count << "]" << endl;
        for(int i = 0; i < Folder+1; i++) {
            bool isLast = i == last;
            listingLast[level] = isLast;

            BasicDocumentType type = (BasicDocumentType) i;
            BasicDocumentObject **docs = getDocuments(type, size);
            if(size > 0) {   
                for(int k = 0; k < level; k++) {
                    stream << (!listingLast[k] ? "|" : " ") << "   ";
                }
                stream << s(5, isLast ? 192 : 195, 196, 196, 196, 194) << " " << getDocumentTypeName(type) << " [" << size << "]" << endl;
                for(int j = 0; j < size; j++) {
                    bool isLast2 = j == size - 1;
                    listingLast[level+1] = isLast2;
                    for(int k = 0; k < level+1; k++) {
                        stream << (!listingLast[k] ? "|" : " ") << "   ";
                    }

                    stream << s(5, isLast2 ? 192 : 195, 196, 196, 196, docs[j]->getType() == Folder ? 0 : 196);
                    
                    if(docs[j]->getType() == Folder) {
                        listingLevel = level + 2;
                        dynamic_cast<BasicDocumentFolder*>(docs[j])->listByTypes();
                    }
                    else
                    {
                        stream << " ";
                        docs[j]->show(false, stream);
                        stream << endl;
                    }
                }
            }
            delete[] docs;
        }

        if(level == 0) {
            listingLevel = 0;
        }
    }
    
    // оператор индексирования (индекс)
    BasicDocumentObject *BasicDocumentFolder::operator [](int key) {
        return get(key);
    }
    
    // оператор индексирования (название)
    BasicDocumentObject *BasicDocumentFolder::operator [](const char *key) {
        for(int i = 0; i < _count; i++) {
            if(strcmp(_children[i]->getTitle(), key) == 0) {
                return _children[i];
            }
        }
        return NULL;
    }
    
    // оператор индексирования (тип)
    BasicDocumentObject **BasicDocumentFolder::operator [](const BasicDocumentType type) {
        int count = 0;
        return getDocuments(type, count);
    }
    
    // динамическое выделение памяти при нехватке
    void BasicDocumentFolder::_reinitMemory() {
        _maxCount = (_maxCount > 0) ? _maxCount*2 : INITIAL_SIZE;
        BasicDocumentObject **newMemory = new BasicDocumentObject*[_maxCount];

        if(_children && _count > 0) {
            for(int i = 0; i < _count; i++) {
                newMemory[i] = _children[i];
            }
        }
        if(_children)
            delete[] _children;
        _children = newMemory;
    }
    
    // сортировка папки
    void BasicDocumentFolder::_sort() {
        for(int i = _count - 1; i >= 0; i--) {
            for(int j = 0; j < i; j++) {
                if(*(_children[j]) > *(_children[j+1])) {
                    BasicDocumentObject *tmp = _children[j];
                    _children[j] = _children[j+1];
                    _children[j+1] = tmp;
                }
            }
        }
    }

    /**
     * -------------------------------------------------------------------
     * DocumentFolder
     */
    // конструктор (название, автор, массив элементов, длина массива)
     DocumentFolder::DocumentFolder(const char *title, DocumentAuthor author, const BasicDocumentObject **documents, int size) :
     BasicDocumentFolder(title, documents, size) {
        _author = author;
    }
    // конструктор копирования
    DocumentFolder::DocumentFolder(const DocumentFolder &folder) {
        *this = folder;
    }
    DocumentFolder::~DocumentFolder() {}

    // получение автора
    const DocumentAuthor DocumentFolder::getAuthor() const {
        return _author;
    }
    // изменение автора
    void DocumentFolder::setAuthor(DocumentAuthor author) {
        _author = author;
    }

    // получение редактора
    const DocumentEditor DocumentFolder::getEditor() const {
        return _editor;
    }
    // изменение редактора
    void DocumentFolder::setEditor(DocumentEditor editor) {
        _editor = editor;
    }

    // изменение редактора
    void DocumentFolder::edit(DocumentEditor editor) {
        return setEditor(editor);
    }

    // клонирование объекта
    BasicDocumentObject *DocumentFolder::clone() const {
        DocumentFolder *newFolder = new DocumentFolder(*this);
        return newFolder;
    }
    // проверка равенства объектов
    bool DocumentFolder::equal(const OrdinaryObject &obj) const {
        if(typeid(*this) == typeid(obj)) {
            DocumentFolder const *real = dynamic_cast<const DocumentFolder *>(&obj);

            bool res = strcmp(_title, real->_title) == 0
            && _count == real->_count;

            if(res) {
                for(int i = 0; i < _count; i++) {
                    if( !(*(_children[i]) == *(real->_children[i]) ) ) {
                        return false;
                    }
                }
            }

            return res;
        }
        return false;
    }
    // вывод информации об объекте
    void DocumentFolder::show(bool full, ostream &stream) const {
        if(full) {
            stream << showStart << "Папка " << showOrDefault(_title, "[название не указано]") << " [" << _count << " элементов]"
            << showNL << "Автор: "; _author.show(false, stream);
            stream
            << showNL << "Редактор: "; _editor.show(false, stream);
            stream << showEnd;
        }
        list();
    }
    
    // оператор присваивания
    DocumentFolder& DocumentFolder::operator = (const DocumentFolder &folder) {
        if(&folder == this) return *this;
        if(_title)
            delete[] _title;
        _title = copyCharString(folder._title);
        _author = folder._author;
        _editor = folder._editor;
        for(int i = 0; i < folder._count; i++) {
            add(folder.get(i));
        }
        return *this;
    }

    // оператор сложения папки и документа
    DocumentFolder DocumentFolder::operator +(const Document &obj) {
        DocumentFolder *newFolder = new DocumentFolder(*this);

        const char *newTitle = concatCharStrings(_title, " + ", obj.getTitle());
        newFolder->setTitle(newTitle);
        delete[] newTitle;

        newFolder->add(obj);
        return *newFolder;
    }
    // оператор сложения папки и папки
    DocumentFolder DocumentFolder::operator +(const DocumentFolder &obj) {
        DocumentFolder *newFolder = new DocumentFolder(*this);

        const char *newTitle = concatCharStrings(_title, " + ", obj.getTitle());
        newFolder->setTitle(newTitle);
        delete[] newTitle;

        for(int i = 0; i < obj._count; i++) {
            newFolder->add(obj._children[i]);
        }
        return *newFolder;
    }
    // оператор вычитания документа из папки
    DocumentFolder DocumentFolder::operator -(const Document &obj) {
        DocumentFolder *newFolder = new DocumentFolder(*this);

        const char *newTitle = concatCharStrings(_title, " - ", obj.getTitle());
        newFolder->setTitle(newTitle);
        delete[] newTitle;

        newFolder->remove(obj);
        return *newFolder;
    }
    // оператор вычитания папки из папки
    DocumentFolder DocumentFolder::operator -(const DocumentFolder &obj) {
        DocumentFolder *newFolder = new DocumentFolder(*this);

        const char *newTitle = concatCharStrings(_title, " - ", obj.getTitle());
        newFolder->setTitle(newTitle);
        delete[] newTitle;

        for(int i = 0; i < obj._count; i++) {
            newFolder->remove(obj._children[i]);
        }
        return *newFolder;
    }

    // оператор присваивания сложения элемента папки
    DocumentFolder& DocumentFolder::operator +=(const BasicDocumentObject &obj) {
        add(obj);
        return *this;
    }
    // оператор присваивания вычитания элемента папки
    DocumentFolder& DocumentFolder::operator -=(const BasicDocumentObject &obj) {
        remove(obj);
        return *this;
    }

    // оператора сложения документа и папки
    DocumentFolder operator + (Document &doc, DocumentFolder &folder) {
        return folder + doc;
    }
};