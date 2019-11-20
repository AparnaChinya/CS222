#include "pfm.h"
#include <fstream>
#include <iostream>
using namespace std;

PagedFileManager *PagedFileManager::_pf_manager = nullptr;

PagedFileManager &PagedFileManager::instance() {
    static PagedFileManager _pf_manager = PagedFileManager();
    return _pf_manager;
}

PagedFileManager::PagedFileManager() = default;

PagedFileManager::~PagedFileManager() { delete _pf_manager; }

PagedFileManager::PagedFileManager(const PagedFileManager &) = default;

PagedFileManager &PagedFileManager::operator=(const PagedFileManager &) = default;

RC PagedFileManager::createFile(const std::string &fileName) {

	//Check if file exists
	fstream file(fileName.c_str());
	if (file.good()) {
		return FAILURE;
	}
	
	//Open the file
	file.open(fileName, ios::out);

	//If file doesnt get created
	if (!file) {
		return FAILURE;
	}

	//Close the file
	file.close();

    return SUCCESS;
}

RC PagedFileManager::destroyFile(const std::string &fileName) {
	
	if (remove(fileName.c_str()) != SUCCESS) {
		return FAILURE;
	}
	return SUCCESS;
	
}

RC PagedFileManager::openFile(const std::string &fileName, FileHandle &fileHandle) {
	//Check if file exists
	fstream file(fileName.c_str());
	if (file.bad()) {
		return FAILURE;
	}

	//Open the file
	file.open(fileName, ios::out);

	if (file.is_open()) {
		return SUCCESS;
	}
	return FAILURE;
}

RC PagedFileManager::closeFile(FileHandle &fileHandle) {
    return -1;
}

FileHandle::FileHandle() {
    readPageCounter = 0;
    writePageCounter = 0;
    appendPageCounter = 0;
}

FileHandle::~FileHandle() = default;

RC FileHandle::readPage(PageNum pageNum, void *data) {
    return -1;
}

RC FileHandle::writePage(PageNum pageNum, const void *data) {
    return -1;
}

RC FileHandle::appendPage(const void *data) {
    return -1;
}

unsigned FileHandle::getNumberOfPages() {
    return -1;
}

RC FileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount) {
    return -1;
}