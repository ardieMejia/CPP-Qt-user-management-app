#include <mycsvutilities.h>



std::vector<std::string> MyParser::parseCSVRow(const std::string& row) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    
    for (char c : row) {
        if (!inQuotes && c == ',') {
            fields.push_back(field);
	    qDebug() << QString::fromStdString(field);
            field.clear();
        } else if (c == '"') {
            inQuotes = !inQuotes;
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    
    return fields;
}
