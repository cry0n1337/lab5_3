#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Класс книги
class Book
{
public:
    Book(const std::string& name,
        const std::string& author,
        int year)
        : name_(name), author_(author), year_(year) {
    }

    const std::string& getName()   const { return name_; }
    const std::string& getAuthor() const { return author_; }
    int                getYear()   const { return year_; }

private:
    std::string name_;
    std::string author_;
    int         year_;
};

// Функтор-сортировщик: сначала по автору, потом по названию
struct BookSorter
{
    bool operator()(const Book* a, const Book* b) const
    {
        if (a->getAuthor() != b->getAuthor())
            return a->getAuthor() < b->getAuthor();
        return a->getName() < b->getName();
    }
};

// Функтор-поисковик: год в диапазоне [minYear, maxYear]
class BookFinder
{
public:
    BookFinder(int minYear, int maxYear)
        : minYear_(minYear), maxYear_(maxYear) {
    }

    bool operator()(const Book* book) const
    {
        int y = book->getYear();
        return y >= minYear_ && y <= maxYear_;
    }

private:
    int minYear_;
    int maxYear_;
};

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    // Коллекция книг
    std::vector<Book*> books;
    books.push_back(new Book("Война и мир", "Толстой Л.Н.", 2010));
    books.push_back(new Book("Подросток", "Достоевский Ф.М.", 2004));
    books.push_back(new Book("Обрыв", "Гончаров И.А.", 2010));
    books.push_back(new Book("Анна Каренина", "Толстой Л.Н.", 1999));
    books.push_back(new Book("Обыкновенная история", "Гончаров И.А.", 2011));
    books.push_back(new Book("Утраченные иллюзии", "Бальзак О.", 2009));
    books.push_back(new Book("Оливер Твист", "Диккенс Ч.", 2001));
    books.push_back(new Book("Фауст", "Гёте И.В.", 2010));
    books.push_back(new Book("Дюина Долина", "Бальзак О.", 1998));

    // 1. Сортировка
    std::cout << "Книги в алфавитном порядке:\n";
    std::sort(books.begin(), books.end(), BookSorter());
    for (const auto& b : books)
        std::cout << b->getAuthor() << " \"" << b->getName() << "\"\n";

    // 2. Поиск книг 2005-2014 гг.
    BookFinder book_finder(2005, 2014);
    std::cout << "\nКниги в диапазоне года издания 2005 - 2014:\n";
    auto it = std::find_if(books.begin(), books.end(), book_finder);
    while (it != books.end())
    {
        std::cout << (*it)->getAuthor() << " \"" << (*it)->getName() << "\"\n";
        it = std::find_if(++it, books.end(), book_finder);
    }

    // Освобождение памяти
    for (auto& b : books) delete b;
    return 0;
}
