#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


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

struct BookSorter
{
    bool operator()(const Book* a, const Book* b) const
    {
        if (a->getAuthor() != b->getAuthor())
            return a->getAuthor() < b->getAuthor();
        return a->getName() < b->getName();
    }
};

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

    std::vector<Book*> books;
    books.push_back(new Book("Âîéíà è ìèð", "Òîëñòîé Ë.Í.", 2010));
    books.push_back(new Book("Ïîäðîñòîê", "Äîñòîåâñêèé Ô.Ì.", 2004));
    books.push_back(new Book("Îáðûâ", "Ãîí÷àðîâ È.À.", 2010));
    books.push_back(new Book("Àííà Êàðåíèíà", "Òîëñòîé Ë.Í.", 1999));
    books.push_back(new Book("Îáûêíîâåííàÿ èñòîðèÿ", "Ãîí÷àðîâ È.À.", 2011));
    books.push_back(new Book("Óòðà÷åííûå èëëþçèè", "Áàëüçàê Î.", 2009));
    books.push_back(new Book("Îëèâåð Òâèñò", "Äèêêåíñ ×.", 2001));
    books.push_back(new Book("Ôàóñò", "Ã¸òå È.Â.", 2010));
    books.push_back(new Book("Äþèíà Äîëèíà", "Áàëüçàê Î.", 1998));

    std::cout << "Êíèãè â àëôàâèòíîì ïîðÿäêå:\n";
    std::sort(books.begin(), books.end(), BookSorter());
    for (const auto& b : books)
        std::cout << b->getAuthor() << " \"" << b->getName() << "\"\n";

    BookFinder book_finder(2005, 2014);
    std::cout << "\nÊíèãè â äèàïàçîíå ãîäà èçäàíèÿ 2005 - 2014:\n";
    auto it = std::find_if(books.begin(), books.end(), book_finder);
    while (it != books.end())
    {
        std::cout << (*it)->getAuthor() << " \"" << (*it)->getName() << "\"\n";
        it = std::find_if(++it, books.end(), book_finder);
    }

    for (auto& b : books) delete b;
    return 0;
}
