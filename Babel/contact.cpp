#include "contact.h"

const std::map<std::string, std::string>&		contact::getContactList() const
{
	return _contact;
}

const std::string&									contact::getContactStatus(const std::string& name) const
{
	if (this->_contact.find(name) != this->_contact.end())
		return this->_contact.find(name)->second;
	return name;
}

void											contact::setContactStatus(const std::string& name, const std::string& status)
{
	_contact.insert(std::make_pair(name, status));
}

void											contact::delContact(const std::string &name)
{
	if (_contact.find(name) != _contact.end())
		_contact.erase(_contact.find(name));
}

const std::map<std::string, int>&				contact::getWaitingList() const
{
	return _waitingContact;
}

void											contact::addWaiting(const std::string &name)
{
	this->_waitingContact.insert(std::make_pair(name, 1));
}

void											contact::delWaiting(const std::string &name)
{
	if (this->_waitingContact.find(name) != this->_waitingContact.end())
		this->_waitingContact.erase(this->_waitingContact.find(name));
}