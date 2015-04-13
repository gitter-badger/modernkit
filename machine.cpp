//
//  machine.cpp
//  modernkit
//
//  Created by Ariel Abreu on 4/11/15.
//  Copyright (c) 2015 ArielAbreu. All rights reserved.
//

#include <iostream>
#include "modernkit.h"
#include "types.h"

using namespace std;
using namespace xercesc;

int initHTML() {
    try {
        XMLPlatformUtils::Initialize();
        return 0;
    } catch (const XMLException& toCatch) {
        char* msg = XMLString::transcode(toCatch.getMessage());
        cout << "INIT_ERR: ";
        cout << msg << endl;
        XMLString::release(&msg);
        return -1;
    }
}

int endHTML() {
    XMLPlatformUtils::Terminate();
    return 0;
}