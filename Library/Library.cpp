#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

struct Book
{
	string author;
	string title;
	string genre;
	string shortDescription;
	int year;
	string tags;
	double rating;
	string uniqueIdentifier;
};

struct User
{
	string userName;
	string password;
	string role;
};

bool compareYears(const Book &lhs, const Book &rhs)
{
	return lhs.year < rhs.year;
}

bool compareRatings(const Book &lhs, const Book &rhs)
{
	return lhs.rating < rhs.rating;
}

void main()
{
	//Information about the administrator

	User *administrator = new User[3];

	administrator->userName = "admin";
	administrator->password = "i<3c++";
	administrator->role = "admin";
	
	//Information about users

	int numberOfUsers = 0;

	ofstream users("Users.txt");

	bool isLogged = false;
	bool isLoggedAsAdmin = false;

	//Adding the administrator

	users << administrator->userName << endl;
	users << administrator->password << endl;
	users << administrator->role << endl;
	users << endl;
	numberOfUsers++;

	users.close();

	//Information about books

	int numberOfBooks = 0;
		
	//Commands

	string loginCommand = "login";
	string logoutCommand = "logout";
	string helpCommand = "help";
	string exitCommand = "exit";
	string booksCommand = "books";
	string usersCommand = "users";
		
	//Starting logo

	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "                                 Library v1.0                                   " << endl;
	cout << "                                Welcome, guest!                                 " << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	//-------------

	while (true)
	{
		cout << "Enter command: (enter help to see all the commands)" << endl;
		cout << endl;

		string command = "";
		getline(cin, command);

		int pos = 0;

		string input = "";
		
		while (command[pos] != '\0' && command[pos] != (char)32)
		{
			input += command[pos];
			pos++;
		}

		if (input == loginCommand)
		{
			//Login
			system("cls");
			
			if (isLogged)
			{
				cout << "You are already logged in." << endl;
				cout << endl;
			}
			else
			{
				string username;
				string password;

				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;

				string userCheck;

				ifstream usersFromTxt("Users.txt");
				int line = 0;
				bool match = false;

				while (userCheck != username && line <= (numberOfUsers * 4))
				{
					getline(usersFromTxt, userCheck);
					line++;

					if (userCheck == username)
					{
						match = true;
					}
				}

				usersFromTxt.close();

				usersFromTxt.open("Users.txt");

				if (!match)
				{
					cout << "Username or password is incorrect" << endl;
					cout << endl;
				}
				else
				{
					string passCheck;

					for (int i = 0; i < line + 1; i++)
					{
						getline(usersFromTxt, passCheck);
					}

					if (passCheck == password)
					{
						cout << endl;
						cout << "Welcome, " << username << "!" << endl;
						cout << endl;

						isLogged = true;
						if (username == "admin")
						{
							isLoggedAsAdmin = true;
						}
					}
					else
					{
						cout << "Username or password is incorrect" << endl;
						cout << endl;
					}
				}

				usersFromTxt.close();
			}
		}
		else if (input == logoutCommand)
		{
			//Logout

			system("cls");
			if (isLogged)
			{
				cout << "You're successfully logout!" << endl;
				cout << endl;

				if (isLoggedAsAdmin)
				{
					isLoggedAsAdmin = false;
				}

				isLogged = false;
			}
			else
			{
				cout << "You're not logged in!" << endl;
				cout << endl;
			}
			
		}
		else if (input == helpCommand)
		{
			//Help menu

			system("cls");

			cout << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "                                    HELP                                 " << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "login - Login in the system, if you already have an account" << endl;
			cout << "logout - Logout from the system, if you are already logged in" << endl;
			cout << "exit - If you want to exit from the program" << endl;
			cout << "books all - View all existing books" << endl;
			cout << "books info <isbn_value> - Show all the info about the book with this ISBN" << endl;
			cout << "books find <option> <option_str>- Search book." << endl;
			cout << "                                  <option> is {“title” , “author”, “tag”}" << endl;
			cout << "                                  <option_str> is the searching criteria" << endl;
			cout << "books sort <option> - Sort all books and show them." << endl;
			cout << "                      <option> is  {“year”, “rating”}" << endl;
			cout << endl;
			cout << "For administrators only: " << endl;
			cout << endl;
			cout << "books add - To add new book" << endl;
			cout << "books remove - To remove existing user" << endl;
			cout << "users add - To add new user" << endl;
			cout << "users remove - To remove existing user" << endl;
			cout << endl;
		}
		else if (input == exitCommand)
		{
			//Exit

			system("cls");

			break;
		}
		else if (input == booksCommand)
		{
			//Books operations

			string subCommand = "";
			bool startReading = false;
			int numberOfIntervals = 0;

			for (int i = 0; i < command.length(); i++)
			{
				if (command[i] == ' ')
				{
					startReading = !startReading;
					numberOfIntervals++;

					if (numberOfIntervals >= 2)
					{
						break;
					}
				}

				if (startReading && command[i] != ' ')
				{
					subCommand += command[i];
				}
			}

			//Next action is depending on the subcommand

			if (subCommand == "add")
			{
				//Add new book

				system("cls");

				if (isLoggedAsAdmin)
				{
					//Add books

					list<Book> booksToAdd;

					while (true)
					{
						cout << "Add new book? (y/Y - yes, n/N - no)" << endl;
						char answer;
						cin >> answer;

						if (answer == 'y' || answer == 'Y')
						{
							Book *newBook = new Book;
							cout << endl;

							getline(cin, newBook->author); //Strange bug without answer, the program just skip some certain getlines
														   //so if add them twice they are just skipped 
							cout << "Author: ";
							getline(cin, newBook->author);
							cout << "Title: ";
							getline(cin, newBook->title);
							cout << "Genre: ";
							getline(cin, newBook->genre);
							cout << "Short description: ";
							getline(cin, newBook->shortDescription);
							cout << "Year: ";
							cin >> newBook->year;

							getline(cin, newBook->tags); //Same problem...

							cout << "Tags (List them only with commas): ";
							getline(cin, newBook->tags);
							cout << "Rating: ";
							cin >> newBook->rating;
							cout << "Unique identifier (ISBN - 13 digits): ";
							cin >> newBook->uniqueIdentifier;
							cout << endl;

							booksToAdd.push_back(*newBook);
						}
						else
						{
							break;
						}
					}

					//Save current books than extend them and after that fill the text file with the new records

					list<Book> correctionList;
					int correctionLine = 1;
					string temp;

					ifstream currentBooks("Books.txt");

					while (correctionLine <= numberOfBooks * 9)
					{
						Book *currBook = new Book;

						getline(currentBooks, temp);
						currBook->author = temp;

						getline(currentBooks, temp);
						currBook->title = temp;

						getline(currentBooks, temp);
						currBook->genre = temp;

						getline(currentBooks, temp);
						currBook->shortDescription = temp;

						getline(currentBooks, temp);
						istringstream(temp) >> currBook->year;
						
						getline(currentBooks, temp);
						currBook->tags = temp;

						getline(currentBooks, temp);
						istringstream(temp) >> currBook->rating;

						getline(currentBooks, temp);
						currBook->uniqueIdentifier = temp;

						getline(currentBooks, temp);

						correctionList.push_back(*currBook);
						correctionLine += 9;
					}

					currentBooks.close();

					for each (Book book in booksToAdd)
					{
						correctionList.push_back(book);
					}

					ofstream books("Books.txt");

					numberOfBooks = 0;

					while (!correctionList.empty())
					{
						books << correctionList.front().author << endl;
						books << correctionList.front().title << endl;
						books << correctionList.front().genre << endl;
						books << correctionList.front().shortDescription << endl;
						books << correctionList.front().year << endl;
						books << correctionList.front().tags << endl;
						books << correctionList.front().rating << endl;
						books << correctionList.front().uniqueIdentifier << endl;
						books << endl;

						correctionList.pop_front();
						numberOfBooks++;
					}

					books.close();
				}
				else
				{
					cout << "You don't have permission to do that!" << endl;
				}
			}
			else if (subCommand == "remove")
			{
				//Remove some book by its ISBN

				if (isLoggedAsAdmin)
				{
					system("cls");

					cout << "Enter the ISBN of the book you want to remove!" << endl;

					string isbnToRemove = "";

					getline(cin, isbnToRemove);

					//Get current books

					list<Book> currentList;
					int correctionLine = 1;
					string temp;

					ifstream currentBooks("Books.txt");

					while (correctionLine <= numberOfBooks * 9)
					{
						Book *currBook = new Book;

						getline(currentBooks, temp);
						currBook->author = temp;

						getline(currentBooks, temp);
						currBook->title = temp;

						getline(currentBooks, temp);
						currBook->genre = temp;

						getline(currentBooks, temp);
						currBook->shortDescription = temp;

						getline(currentBooks, temp);
						istringstream(temp) >> currBook->year;

						getline(currentBooks, temp);
						currBook->tags = temp;

						getline(currentBooks, temp);
						istringstream(temp) >> currBook->rating;

						getline(currentBooks, temp);
						currBook->uniqueIdentifier = temp;

						getline(currentBooks, temp);

						currentList.push_back(*currBook);
						correctionLine += 9;
					}

					currentBooks.close();

					list<Book> newList;

					for each (Book book in currentList)
					{
						if (book.uniqueIdentifier != isbnToRemove)
						{
							newList.push_back(book);
						}
					}
					
					ofstream books("Books.txt");

					numberOfBooks = 0;

					while (!newList.empty())
					{
						books << newList.front().author << endl;
						books << newList.front().title << endl;
						books << newList.front().genre << endl;
						books << newList.front().shortDescription << endl;
						books << newList.front().year << endl;
						books << newList.front().tags << endl;
						books << newList.front().rating << endl;
						books << newList.front().uniqueIdentifier << endl;
						books << endl;

						newList.pop_front();
						numberOfBooks++;
					}

					books.close();
				}
				else
				{
					cout << "You don't have permission to do that!" << endl;
				}
			}
			else if (subCommand == "all")
			{
				//Show all books

				system("cls");

				ifstream books("Books.txt");
				int line = 0;
				string temp = "";

				while (line < numberOfBooks * 9)
				{
					if (line % 9 == 0)
					{
						cout << "============================================================" << endl;
						cout << "Book #" << (line / 9) + 1 << endl;
						cout << "============================================================" << endl;
					}
					
					getline(books, temp);

					cout << temp << endl;

					line++;
				}
			}
			else if (subCommand == "find")
			{
				//Search for some book

				system("cls");

				string option = "";
				bool startReading = false;
				int numberOfIntervals = 0;

				for (int i = 0; i < command.length(); i++)
				{
					if (command[i] == ' ')
					{
						if (numberOfIntervals >= 1)
						{
							startReading = !startReading;
						}

						numberOfIntervals++;

						if (numberOfIntervals > 2)
						{
							break;
						}
					}

					if (startReading && command[i] != ' ')
					{
						option += command[i];
					}
				}

				string searchingCriteria = "";
				startReading = false;
				numberOfIntervals = 0;

				for (int i = 0; i < command.length(); i++)
				{
					if (numberOfIntervals < 3)
					{
						if (command[i] == ' ')
						{
							if (numberOfIntervals >= 2)
							{
								startReading = !startReading;
							}

							numberOfIntervals++;
						}
					}

					if (startReading)
					{
						if (numberOfIntervals <= 3)
						{
							if (command[i] != ' ')
							{
								searchingCriteria += command[i];
							}
							else
							{
								numberOfIntervals++;
							}
						}
						else
						{
							searchingCriteria += command[i];
						}
					}
				}

				//Now just search for "searchingCriteria" in "option" properties

				list<Book> searchingList;
				int correctionLine = 1;
				string temp;

				ifstream currentBooks("Books.txt");

				while (correctionLine <= numberOfBooks * 9)
				{
					Book *currBook = new Book;

					getline(currentBooks, temp);
					currBook->author = temp;

					getline(currentBooks, temp);
					currBook->title = temp;

					getline(currentBooks, temp);
					currBook->genre = temp;

					getline(currentBooks, temp);
					currBook->shortDescription = temp;

					getline(currentBooks, temp);
					istringstream(temp) >> currBook->year;

					getline(currentBooks, temp);
					currBook->tags = temp;

					getline(currentBooks, temp);
					istringstream(temp) >> currBook->rating;

					getline(currentBooks, temp);
					currBook->uniqueIdentifier = temp;

					getline(currentBooks, temp);

					searchingList.push_back(*currBook);
					correctionLine += 9;
				}

				currentBooks.close();

				for each (Book book in searchingList)
				{
					if (option == "title")
					{
						if (book.title == searchingCriteria)
						{
							cout << "Result found!" << endl;
							cout << "--------------------------------------" << endl;
							cout << "Author: " << book.author << endl;
							cout << "Title: " << book.title << endl;
							cout << "Genre: " << book.genre << endl;
							cout << "Short description: " << book.shortDescription << endl;
							cout << "Year: " << book.year << endl;
							cout << "Tags: " << book.tags << endl;
							cout << "Rating: " << book.rating << endl;
							cout << "ISBN: " << book.uniqueIdentifier << endl;
							cout << endl;
							cout << "--------------------------------------" << endl;
						}
					}
					else if (option == "tag")
					{
						string tags = book.tags;
						list<string> separatedTags;
						string tag = "";
						int numberOfCommas = 0;

						//Separate tags from input

						for (int i = 0; i < tags.length(); i++)
						{
							if (tags[i] != ',')
							{
								tag += tags[i];
								if (i == tags.length() - 1)
								{
									separatedTags.push_back(tag);
								}
							}
							else
							{
								separatedTags.push_back(tag);
								tag = "";
							}
						}

						for each (string tag in separatedTags)
						{
							if (tag == searchingCriteria)
							{
								cout << "Result found!" << endl;
								cout << "--------------------------------------" << endl;
								cout << "Author: " << book.author << endl;
								cout << "Title: " << book.title << endl;
								cout << "Genre: " << book.genre << endl;
								cout << "Short description: " << book.shortDescription << endl;
								cout << "Year: " << book.year << endl;
								cout << "Tags: " << book.tags << endl;
								cout << "Rating: " << book.rating << endl;
								cout << "ISBN: " << book.uniqueIdentifier << endl;
								cout << endl;
								cout << "--------------------------------------" << endl;
							}
						}
					}
					else if (option == "author")
					{
						if (book.author == searchingCriteria)
						{
							cout << "Result found!" << endl;
							cout << "--------------------------------------" << endl;
							cout << "Author: " << book.author << endl;
							cout << "Title: " << book.title << endl;
							cout << "Genre: " << book.genre << endl;
							cout << "Short description: " << book.shortDescription << endl;
							cout << "Year: " << book.year << endl;
							cout << "Tags: " << book.tags << endl;
							cout << "Rating: " << book.rating << endl;
							cout << "ISBN: " << book.uniqueIdentifier << endl;
							cout << endl;
							cout << "--------------------------------------" << endl;
						}
					}
				}

				
				ofstream books("Books.txt");

				numberOfBooks = 0;

				while (!searchingList.empty())
				{
					books << searchingList.front().author << endl;
					books << searchingList.front().title << endl;
					books << searchingList.front().genre << endl;
					books << searchingList.front().shortDescription << endl;
					books << searchingList.front().year << endl;
					books << searchingList.front().tags << endl;
					books << searchingList.front().rating << endl;
					books << searchingList.front().uniqueIdentifier << endl;
					books << endl;

					searchingList.pop_front();
					numberOfBooks++;
				}

				books.close();
			}
			else if (subCommand == "sort")
			{
				//Sorting

				string option = "";
				bool startReading = false;
				int numberOfIntervals = 0;

				for (int i = 0; i < command.length(); i++)
				{
					if (command[i] == ' ')
					{
						if (numberOfIntervals >= 1)
						{
							startReading = !startReading;
						}

						numberOfIntervals++;

						if (numberOfIntervals > 2)
						{
							break;
						}
					}

					if (startReading && command[i] != ' ')
					{
						option += command[i];
					}
				}

				list<Book> currentList;
				int correctionLine = 1;
				string temp;

				ifstream currentBooks("Books.txt");

				while (correctionLine <= numberOfBooks * 9)
				{
					Book *currBook = new Book;

					getline(currentBooks, temp);
					currBook->author = temp;

					getline(currentBooks, temp);
					currBook->title = temp;

					getline(currentBooks, temp);
					currBook->genre = temp;

					getline(currentBooks, temp);
					currBook->shortDescription = temp;

					getline(currentBooks, temp);
					istringstream(temp) >> currBook->year;

					getline(currentBooks, temp);
					currBook->tags = temp;

					getline(currentBooks, temp);
					istringstream(temp) >> currBook->rating;

					getline(currentBooks, temp);
					currBook->uniqueIdentifier = temp;

					getline(currentBooks, temp);

					currentList.push_back(*currBook);
					correctionLine += 9;
				}

				currentBooks.close();
				
				if (option == "year")
				{
					currentList.sort(&compareYears);
				}
				else if (option == "rating")
				{
					currentList.sort(&compareRatings);
				}

				ofstream books("Books.txt");

				numberOfBooks = 0;

				while (!currentList.empty())
				{
					books << currentList.front().author << endl;
					books << currentList.front().title << endl;
					books << currentList.front().genre << endl;
					books << currentList.front().shortDescription << endl;
					books << currentList.front().year << endl;
					books << currentList.front().tags << endl;
					books << currentList.front().rating << endl;
					books << currentList.front().uniqueIdentifier << endl;
					books << endl;

					currentList.pop_front();
					numberOfBooks++;
				}

				books.close();

				cout << "Enter (books all) to see the result!" << endl;
			}
			else if (subCommand == "info")
			{
				system("cls");

				string isbnValue = "";
				bool startReading = false;
				int numberOfIntervals = 0;

				for (int i = 0; i < command.length(); i++)
				{
					if (command[i] == ' ')
					{
						if (numberOfIntervals >= 1)
						{
							startReading = !startReading;
						}

						numberOfIntervals++;

						if (numberOfIntervals > 2)
						{
							break;
						}
					}

					if (startReading && command[i] != ' ')
					{
						isbnValue += command[i];
					}
				}

				//Now find the book with this ISBN number

				ifstream books("Books.txt");
				string temp;
				int searchingPos = 0;

				while (temp != isbnValue && searchingPos <= numberOfBooks * 9)
				{
					getline(books, temp);
					searchingPos++;
				}

				books.close();

				books.open("Books.txt");

				for (int i = 0; i < searchingPos - 8; i++)
				{
					getline(books, temp);
				}

				getline(books, temp);
				cout << "Author: " << temp << endl;
				getline(books, temp);
				cout << "Title: " << temp << endl;
				getline(books, temp);
				cout << "Genre: " << temp << endl;
				getline(books, temp);
				cout << "Short description: " << temp << endl;
				getline(books, temp);
				cout << "Year: " << temp << endl;
				getline(books, temp);
				cout << "Tags: " << temp << endl;
				getline(books, temp);
				cout << "Rating: " << temp << endl;
				getline(books, temp);
				cout << "ISBN: " << temp << endl;
				cout << endl;

				books.close();
			}
		}
		else if (input == usersCommand)
		{
			string subCommand = "";
			bool startReading = false;
			int numberOfIntervals = 0;

			for (int i = 0; i < command.length(); i++)
			{
				if (command[i] == ' ')
				{
					startReading = !startReading;
					numberOfIntervals++;

					if (numberOfIntervals >= 2)
					{
						break;
					}
				}

				if (startReading && command[i] != ' ')
				{
					subCommand += command[i];
				}
			}

			//Next action is depending on the subcommand

			if (subCommand == "add")
			{
				system("cls");

				if (isLoggedAsAdmin)
				{
					list<User> usersToAdd;

					while (true)
					{
						cout << "Add new user? (y/Y - yes, n/N - no)" << endl;
						char answer;
						cin >> answer;

						if (answer == 'y' || answer == 'Y')
						{
							User *newUser = new User;

							getline(cin, newUser->userName); //Strange bug without answer, the program just skip some certain getlines
															 //so if add them twice they are just skipped 
							cout << "Username: ";
							getline(cin, newUser->userName);
							cout << "Password: ";
							getline(cin, newUser->password);
							cout << "Role (admin / user): ";
							getline(cin, newUser->role);

							usersToAdd.push_back(*newUser);
						}
						else
						{
							break;
						}
					}

					//Save current users than, extend them and after that fill the text file with the new records

					list<User> correctionList;
					int correctionLine = 1;
					string temp;

					ifstream currentUsers("Users.txt");

					while (correctionLine <= numberOfUsers * 4)
					{
						User *currUser = new User;

						getline(currentUsers, temp);
						currUser->userName = temp;
						
						getline(currentUsers, temp);
						currUser->password = temp;

						getline(currentUsers, temp);
						currUser->role = temp;

						getline(currentUsers, temp);

						correctionList.push_back(*currUser);
						correctionLine += 4;
					}

					currentUsers.close();

					for each (User user in usersToAdd)
					{
						correctionList.push_back(user);
					}
					
					ofstream users("Users.txt");

					numberOfUsers = 0;

					while (!correctionList.empty())
					{
						users << correctionList.front().userName << endl;
						users << correctionList.front().password << endl;
						users << correctionList.front().role << endl;
						users << endl;

						correctionList.pop_front();
						numberOfUsers++;
					}

					users.close();
				}
				else
				{
					cout << "You don't have permission to do that!" << endl;
				}
			}
			else if (subCommand == "remove")
			{
				system("cls");

				if (isLoggedAsAdmin)
				{
					system("cls");

					cout << "Enter the username of the user you want to remove!" << endl;

					string userToRemove = "";

					getline(cin, userToRemove);

					//Get current users

					list<User> currentList;
					int correctionLine = 1;
					string temp;

					ifstream currentUsers("Users.txt");

					while (correctionLine <= numberOfUsers * 4)
					{
						User *currUser = new User;

						getline(currentUsers, temp);
						currUser->userName = temp;

						getline(currentUsers, temp);
						currUser->password = temp;

						getline(currentUsers, temp);
						currUser->role = temp;

						getline(currentUsers, temp);

						currentList.push_back(*currUser);
						correctionLine += 4;
					}

					currentUsers.close();

					list<User> newList;

					for each (User user in currentList)
					{
						if (user.userName != userToRemove)
						{
							newList.push_back(user);
						}
					}

					ofstream users("Users.txt");

					numberOfUsers = 0;

					while (!newList.empty())
					{
						users << newList.front().userName << endl;
						users << newList.front().password << endl;
						users << newList.front().role << endl;
						users << endl;

						newList.pop_front();
						numberOfUsers++;
					}

					users.close();
				}
				else
				{
					cout << "You don't have permission to do that!" << endl;
				}
			}
		}
	}
	system("cls");
}