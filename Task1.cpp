#include <iostream>
#include <list>
using namespace std;

class Set
{
public:

	struct setList
	{
		int elements;
		setList* next;
		setList(int value) : elements(value), next(nullptr) {};
	};


	setList* firstPointer = nullptr, * temporaryPointer = nullptr, * helpPointer = nullptr;
	int buffer = 0;

	bool checkContains(int elements)
	{
		setList* tempPointer = firstPointer;

		while (tempPointer != nullptr)
		{
			if (tempPointer->elements == elements) return true;
			tempPointer = tempPointer->next;
		}

		return false;
	}

	void inputSet()
	{
		int i = 0;
		cout << "Please enter the unique values of the elements of the set, separated by a SPACE, in one line, to complete the entry, press ENTER:" << endl;
		cin >> buffer;
		temporaryPointer = new setList(buffer);
		firstPointer = temporaryPointer;
		for (i = 0; i < 4; ++i)
		{
			cin >> buffer;
			temporaryPointer->next = new setList(buffer);
			temporaryPointer = temporaryPointer->next;
		}
	}

	void outputSet()
	{
		setList* temporPointer = firstPointer;

		if (!temporPointer)
		{
			cout << "Empty set" << endl;
			return;
		}

		cout << temporPointer->elements << endl;

		if (!(temporPointer->next)) return;

		do
		{
			temporPointer = temporPointer->next;
			cout << temporPointer->elements << endl;
		} while (temporPointer->next != nullptr);

		cout << endl;
		return;
	}

	void deleteSet()
	{
		temporaryPointer = firstPointer;

		if (!temporaryPointer) return;

		do
		{
			helpPointer = temporaryPointer->next;
			temporaryPointer->next = nullptr;
			delete temporaryPointer;
			temporaryPointer = helpPointer;
		} while (helpPointer != nullptr);

		cout << "Memory is free" << endl;
	}

	void getElement()
	{
		cout << "Please, enter the unique value of the elements:" << endl;
		cin >> buffer;
		if (!checkContains(buffer))
		{
			temporaryPointer = firstPointer;
			if (!temporaryPointer)
			{
				temporaryPointer = new setList(buffer);
				return;
			}

			while (temporaryPointer->next != nullptr)
			{
				temporaryPointer = temporaryPointer->next;
			}
			temporaryPointer->next = new setList(buffer);
			return;
		}
		else cout << "Non-unique values" << endl;
	}

	void deleteElement()
	{
		temporaryPointer = firstPointer;
		if (!temporaryPointer)
		{
			cout << "You can't delete the elements because set is empty" << endl;
			return;
		}
		outputSet();
		cout << "Please enter the values of the elements which you want to delete: " << endl;
		cin >> buffer;
		temporaryPointer = firstPointer;

		if (checkContains(buffer))
		{
			if (temporaryPointer->next == nullptr)
			{
				firstPointer = nullptr;
				delete temporaryPointer;
				return;
			}

			if (temporaryPointer->elements == buffer)
			{
				firstPointer = temporaryPointer->next;
				delete temporaryPointer;
				return;
			}

			helpPointer = temporaryPointer;
			temporaryPointer = temporaryPointer->next;

			do
			{
				if (temporaryPointer->elements == buffer)
				{
					helpPointer->next = temporaryPointer->next;
					temporaryPointer->next = nullptr;
					delete temporaryPointer;
					return;
				}
				helpPointer = temporaryPointer;
				temporaryPointer = temporaryPointer->next;
			} while (true);
		}
		else
		{
			cout << "Warning: you enter the non-unique values, it is not recorded:" << buffer << endl;
			return;
		}
	}

	Set operator* (Set& secondSet)
	{
		Set temporarySet{};
		int value;

		temporaryPointer = firstPointer;

		if (!temporaryPointer)
		{
			temporarySet.firstPointer = nullptr;
			return temporarySet;
		}

		temporarySet.temporaryPointer = new setList(0);
		temporarySet.firstPointer = temporarySet.temporaryPointer;



		do
		{
			value = temporaryPointer->elements;
			if (secondSet.checkContains(value))
			{
				temporarySet.temporaryPointer->next = new setList(value);
				temporarySet.temporaryPointer = temporarySet.temporaryPointer->next;
			}
			temporaryPointer = temporaryPointer->next;
		} while (temporaryPointer != nullptr);

		temporarySet.temporaryPointer = temporarySet.firstPointer;
		temporarySet.firstPointer = temporarySet.temporaryPointer->next;
		delete temporarySet.temporaryPointer;


		return temporarySet;
	}

	Set operator+ (Set& secondSet)
	{
		Set temporarySet;
		setList* timePointer = secondSet.firstPointer;
		int value = 0;

		temporaryPointer = firstPointer;

		if (temporaryPointer == nullptr)
		{
			if (timePointer != nullptr)
			{
				temporarySet.firstPointer = nullptr;
				return temporarySet;
			}

			temporarySet.temporaryPointer = new setList(0);
			temporarySet.firstPointer = temporarySet.temporaryPointer;

			do
			{
				temporarySet.temporaryPointer->next = new setList(timePointer->elements);
				temporarySet.temporaryPointer = temporarySet.temporaryPointer->next;
				timePointer = timePointer->next;
			} while (timePointer != nullptr);

			temporarySet.temporaryPointer = temporarySet.firstPointer;
			temporarySet.firstPointer = temporarySet.temporaryPointer->next;
			delete temporarySet.temporaryPointer;
			return temporarySet;
		}

		temporarySet.temporaryPointer = new setList(0);
		temporarySet.firstPointer = temporarySet.temporaryPointer;

		do
		{
			temporarySet.temporaryPointer->next = new setList(temporaryPointer->elements);
			temporarySet.temporaryPointer = temporarySet.temporaryPointer->next;
			temporaryPointer = temporaryPointer->next;
		} while (temporaryPointer != nullptr);

		timePointer = secondSet.firstPointer;

		if (timePointer == nullptr)
		{
			temporarySet.temporaryPointer = temporarySet.firstPointer;
			temporarySet.firstPointer = temporarySet.temporaryPointer->next;
			delete temporarySet.temporaryPointer;
			return temporarySet;
		}

		timePointer = secondSet.firstPointer;
		while (timePointer != nullptr)
		{
			if (!checkContains(timePointer->elements))
			{
				temporarySet.temporaryPointer->next = new setList(timePointer->elements);
				temporarySet.temporaryPointer = temporarySet.temporaryPointer->next;
			}
			timePointer = timePointer->next;
		}

		temporarySet.temporaryPointer = temporarySet.firstPointer;
		temporarySet.firstPointer = temporarySet.temporaryPointer->next;
		delete temporarySet.temporaryPointer;
		return temporarySet;
	}

	Set operator- (Set& secondSet)
	{
		Set temporarySet{};
		setList* timePointer = secondSet.firstPointer;
		int value = 0;

		temporaryPointer = firstPointer;

		if (!temporaryPointer)
		{
			temporarySet.firstPointer = nullptr;
			return temporarySet;
		}

		temporarySet.temporaryPointer = new setList(0);
		temporarySet.firstPointer = temporarySet.temporaryPointer;

		timePointer = secondSet.firstPointer;
		temporaryPointer = firstPointer;


		do
		{
			value = temporaryPointer->elements;
			if (!(secondSet.checkContains(value)))
			{
				temporarySet.temporaryPointer->next = new setList(value);
				temporarySet.temporaryPointer = temporarySet.temporaryPointer->next;
			}
			temporaryPointer = temporaryPointer->next;
		} while (temporaryPointer != nullptr);

		temporarySet.temporaryPointer = temporarySet.firstPointer;
		temporarySet.firstPointer = temporarySet.firstPointer->next;
		delete temporarySet.temporaryPointer;
		return temporarySet;
	}

};

int main()
{
	Set firstSet, secondSet, crossSet, differenceSet{}, unionSet;
	int option, number;
	bool flag = true;

	firstSet.inputSet();
	secondSet.inputSet();

	cout << "Choose: 1. Add element to set 2. Remove element from set 3. Merge sets 4. Intersect sets 5. Difference of sets 6. Output set 7. Terminate program execution" << endl;

	while (flag)
	{
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Choose which set you want to add the element to: 1. First 2. Second" << endl;
			cin >> number;
			switch (number)
			{
			case 1:
				firstSet.getElement();
				continue;
			case 2:
				secondSet.getElement();
				continue;
			default:
				cout << "Invalid value entered" << endl;
				continue;
			}
			continue;

		case 2:
			cout << "Choose which set you want to remove the element to: 1. First 2. Second" << endl;
			cin >> number;
			switch (number)
			{
			case 1:
				firstSet.deleteElement();
				continue;
			case 2:
				secondSet.deleteElement();
				continue;
			default:
				cout << "Invalid value entered" << endl;
				continue;
			}
			continue;

		case 3:
			unionSet = firstSet + secondSet;
			continue;
		case 4:
			crossSet = firstSet * secondSet;
			continue;
		case 5:
			differenceSet = firstSet - secondSet;
			continue;
		case 6:
			cout << "First set: " << endl;
			firstSet.outputSet();
			cout << "Second set: " << endl;
			secondSet.outputSet();
			cout << "Union set: " << endl;
			unionSet.outputSet();
			cout << "Cross set: " << endl;
			crossSet.outputSet();
			cout << "Difference set: " << endl;
			differenceSet.outputSet();
			continue;
		case 7:
			flag = false;
			continue;
		default:
			cout << "Invalid value entered" << endl;
			continue;
		}
	}

	firstSet.deleteSet();
	secondSet.deleteSet();
	unionSet.deleteSet();
	crossSet.deleteSet();
	differenceSet.deleteSet();
	return 0;
}