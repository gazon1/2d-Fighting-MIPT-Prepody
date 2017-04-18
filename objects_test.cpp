#include "project.h"
#include "stdio.h"

void calculateCount(Object & object, int & count);
void verifyCount(const int count, const int shouldBeThat);
void verifyObject(const Object * object, const Object * shouldBeThat);
void verifyException(int error, int shouldBeThat);
int  testSuccseed();
void testFailed();

int main()
{
	ArrayOfObjects testObjectsArray;
		
	const int notTooMuch = 10, wayTooMuch = 100;
	int count = 0, forEachCheckCount = 0;
	Object * testObjects[notTooMuch];

	for(int count = 0; count < notTooMuch; count++)
	{
		testObjects[count] = new Object();
		testObjectsArray.addObject(testObjects[count]);
	}

	testObjectsArray.forEach(calculateCount, forEachCheckCount);

	verifyCount(forEachCheckCount, notTooMuch);
	verifyCount(testObjectsArray.count(), notTooMuch);

	for(auto iter = testObjectsArray.begin(); iter != testObjectsArray.end(); ++iter, count++)
	{
		verifyObject(iter.object(), testObjects[count]);
		verifyObject(testObjectsArray[count], testObjects[count]);
	}

	verifyObject(testObjectsArray.first(), testObjects[0]);
	verifyObject(testObjectsArray.last(),  testObjects[notTooMuch-1]);
	
	try
	{
		testObjectsArray[wayTooMuch];
	}
	catch(ArrayOfObjects::exceptions exception)
	{
		verifyException(exception, ArrayOfObjects::indexOutOfRangeException);
	}

	try
	{
		++testObjectsArray.end();
	}
	catch(ArrayOfObjects::exceptions exception)
	{
		verifyException(exception, ArrayOfObjects::iterOutOfRangeException);
	}

	try
	{
		testObjectsArray.deleteObject(nullptr);
	}
	catch(ArrayOfObjects::exceptions exception)
	{
		verifyException(exception, ArrayOfObjects::notFoundException);
	}

	try
	{
		testObjectsArray.addObject(nullptr);
	}
	catch(ArrayOfObjects::exceptions exception)
	{
		verifyException(exception, ArrayOfObjects::nullPtrException);
	}

	try
	{
		count = 0;
		while(count++ < arrayOfObjectsCapacity)
			testObjectsArray.addObject(*testObjects);
	}
	catch(ArrayOfObjects::exceptions exception)
	{
		verifyException(exception, ArrayOfObjects::overflowException);
		testSuccseed();
	}

	testFailed();
}

void calculateCount(Object & object, int & count)
{
	if(object.isActive())
		count++;
};

void verifyObject(const Object * object, const Object * shouldBeThat)
{
	if(object == shouldBeThat)
		return;

	testFailed();
}

void verifyCount(int count, int shouldBeThat)
{
	if(count == shouldBeThat)
		return;

	testFailed();
}

void verifyException(int error, int shouldBeThat)
{
	if(error == shouldBeThat)
		return;

	testFailed();
}

int testSuccseed()
{
	cout << "test succseed!\n";
	exit(0);
}

void testFailed()
{
	cout << "test failed!\n";
	exit(-1);
}