#ifndef CONTACT
# define CONTACT

#include <iostream>
#include <string>
#include <map>
#include <list>

class		contact
{

public:
	const std::map<std::string, std::string>&	getContactList() const;
	const std::string&							getContactStatus(const std::string&)const ;

	void										setContactStatus(const std::string&, const std::string&);
	void										delContact(const std::string&);

	const std::map<std::string, int>&			getWaitingList() const;
	void										addWaiting(const std::string&);
	void										delWaiting(const std::string&);

private:
	std::map<std::string, std::string>			_contact;
	std::map<std::string, int>					_waitingContact;
};

#endif