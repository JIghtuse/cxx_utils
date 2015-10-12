#include <iostream>
#include <tinyxml.h>

using namespace std;

void usage(const char* program_name)
{
    cerr << "Usage: " << program_name << " filename.xml tag1 [ tag2 .. ]\n";
}

TiXmlElement* get_element(TiXmlElement* parent, int ntags, char** tags)
{
    if (parent == nullptr)
        return nullptr;

    TiXmlElement* elem = parent->FirstChildElement(tags[0]);
    if (ntags == 1)
        return elem;

    return get_element(elem, ntags - 1, tags + 1);
}

const char* get_value(TiXmlDocument& doc, int ntags, char** tags)
{
    TiXmlElement* child = get_element(doc.RootElement(), ntags, tags);
    if (!child)
        return nullptr;
    return child->GetText();
}

// Extracts value form xml file
int main(int argc, char *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return 1;
    }

    const char* program = argv[1];

    TiXmlDocument doc(program);
    if (!doc.LoadFile()) {
        cout << "can't load file " << program << endl;
        return 1;
    }
    const char *value = get_value(doc, argc - 2, argv + 2);

    if (!value)
        return 1;

    cout << value << endl;
    return 0;
}
