/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Ariel Abreu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include "modernkit.h"
#include "types.h"


using namespace std;
using namespace xercesc;

Parser* parseHTML(std::string contents) {
  try {
    XMLPlatformUtils::Initialize();
  } catch (const XMLException& toCatch) {
    char* msg = XMLString::transcode(toCatch.getMessage());
    cout << "INIT_ERR:" << endl;
    cout << msg << endl;
    XMLString::release(&msg);
    return NULL;
  }

  XercesDOMParser* parser = new XercesDOMParser();
  parser->setValidationScheme(XercesDOMParser::Val_Always);
  parser->setDoNamespaces(true);

  ErrorHandler* err = (ErrorHandler*) new HandlerBase();
  parser->setErrorHandler(err);

  try {
		MemBufInputSource xml((const XMLByte*)contents.c_str(), contents.size(), "html", false);
    parser->parse(xml);
		parser->adoptDocument();
		delete parser;
		delete err;
		XMLPlatformUtils::Terminate();
		return parser;
  } catch (const XMLException &toCatch) {
    char* msg = XMLString::transcode(toCatch.getMessage());
    cout << "XML_ERR: ";
    cout << msg << endl;
    XMLString::release(&msg);
    return parser;
  } catch (const DOMException &toCatch) {
    char* msg = XMLString::transcode(toCatch.getMessage());
    cout << "DOM_ERR: ";
    cout << msg << endl;
    XMLString::release(&msg);
    return parser;
  } catch (const SAXException &toCatch) {
		char* msg = XMLString::transcode(toCatch.getMessage());
		cout << "SAX_ERR: ";
		cout << msg << endl;
		XMLString::release(&msg);
		return parser;
	} catch (...) {
		cout << "!UNKNOWN_ERR!" << endl;
		return parser;
	}

  delete parser;
  delete err;

  XMLPlatformUtils::Terminate();

  return NULL;
}
