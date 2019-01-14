/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CDatabase.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a template class CDatabase.
* 					The class CDatabase is used to hold the information
* 					of elements in an associative container.
*
****************************************************************************/

#ifndef CDATABASE_H_
#define CDATABASE_H_

template<class T1, class T2>
class CDatabase {
public:

	typedef std::map<T1, T2> 						Database_Container_t;
	typedef typename std::map<T1, T2>::iterator 	Database_Container_Itr_t;

    /**
	 * CDatabase constructor
	 */
	CDatabase();

	/**
	 * CDatabase destructor
	 */
	~CDatabase();

    /**
	 * Add an element to the database
	 * param@ T1 const &key				-	a key to associative container (IN)
	 * param@ T2 const &elem			-	an element to be added   (IN)
	 * returnvalue@ void
	 */
    void addElement(T1 const &key, T2 const &elem);

    /**
	 * Get pointer to an element from the Database which matches the key
	 * param@ T1 elemIdentifier		-	Identifier for an element	(IN)
	 * returnvalue@ T2*				-	Pointer to the element in the database
	 */
    T2* getPointerToElement(T1 elemIdentifier);

    /**
     * Get Elements' container from the Database
     * returnvalue@ Database_Container_t	-	Elements in the Database	(OUT)
     */
    const Database_Container_t getElementsFromDatabase() const;

    /**
	 * Resets the Database
	 * returnvalue@ void
	 */
	void resetDatabase();

	/**
	 * Print all the elements in the database
	 * returnvalue@ void
	 */
	void print();

private:

	/**
	 * An Associative container to store Key and Element.
	 * key 		- name
	 * value	- POI
	 */
	Database_Container_t 				m_container;
};


/**
 * CDatabase constructor
 */
template<class T1, class T2>
CDatabase<T1, T2>::CDatabase()
{
	// do nothing
}


/**
 * CDatabase destructor
 */
template<class T1, class T2>
CDatabase<T1, T2>::~CDatabase()
{
	// do nothing
}


/**
 * Add an element to the database
 * param@ T1 const &key				-	a key to associative container (IN)
 * param@ T2 const &elem			-	an element to be added   (IN)
 * returnvalue@ void
 */
template<class T1, class T2>
void CDatabase<T1, T2>::addElement(T1 const &key, T2 const &elem)
{
	std::pair<CDatabase<T1, T2>::Database_Container_Itr_t, bool> 	ret;

	ret = this->m_container.insert(std::pair<T1, T2>(key, elem));

	if (ret.second == false)
	{
		std::cout << "WARNING: Element already exists in the Database.\n";
		std::cout << "Key = " << key << std::endl;
		std::cout << "Element = " << elem << std::endl;
	}
}


/**
 * Get pointer to an element from the Database which matches the key
 * param@ T1 elemIdentifier		-	Identifier for an element	(IN)
 * returnvalue@ T2*				-	Pointer to the element in the database
 */
template<class T1, class T2>
T2* CDatabase<T1, T2>::getPointerToElement(T1 elemIdentifier)
{
	T2 	*pT2 = 0;

	if (!this->m_container.empty())
	{
		CDatabase<T1, T2>::Database_Container_Itr_t 	itr = this->m_container.find(elemIdentifier);

		if (itr != this->m_container.end())
		{
			// element found
			pT2 = &itr->second;
		}
	}

	return pT2;
}


/**
 * Get Elements' container from the Database
 * returnvalue@ Database_Container_t	-	Elements in the Database	(OUT)
 */
template<class T1, class T2>
const typename CDatabase<T1, T2>::Database_Container_t CDatabase<T1, T2>::getElementsFromDatabase() const
{
	return (this->m_container);
}


/**
 * Resets the Database
 * returnvalue@ void
 */
template<class T1, class T2>
void CDatabase<T1, T2>::resetDatabase()
{
	this->m_container.clear();
}


/**
 * Print all the elements in the database
 * returnvalue@ void
 */
template<class T1, class T2>
void CDatabase<T1, T2>::print()
{
	for (CDatabase<T1, T2>::Database_Container_Itr_t itr = this->m_container.begin(); itr != this->m_container.end(); ++itr)
	{
		std::cout << itr->second << std::endl;
	}
}

#endif /* CDATABASE_H_ */
