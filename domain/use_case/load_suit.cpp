#include "load_suit.h"

LoadSuit::LoadSuit(QObject *parent)
    : QObject{parent}
{}

void LoadSuit::operator()(QString src)
{
    SuitLoaded(serializer->deserialize(fileReader->readFile(src)));
}
