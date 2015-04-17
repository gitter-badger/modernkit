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
#include <string>
#include <vector>
#include "modernkit.h"
#include "typecode.h"

namespace MK {
    namespace HTML {
        HTMLElement* getHead(HTMLDocument* doc) {
            initHTML();
            HTMLElement* root = doc->getDocumentElement();
            HTMLArray* rootelms = root->getChildNodes();
            HTMLElement* returnElm;
            for (int i = 1; i < rootelms->getLength(); i++) {
                HTMLElement* currelm = rootelms->item(i);
                char* nodeName = xercesc::XMLString::transcode(currelm->getNodeName());
                std::string str(nodeName);
                if (str == "head") {
                    xercesc::XMLString::release(&nodeName);
                    returnElm = currelm;
                    return returnElm;
                }
                xercesc::XMLString::release(&nodeName);
            }
            endHTML();
            return NULL;
        }
        HTMLElement* getBody(HTMLDocument* doc) {
            initHTML();
            HTMLElement* root = doc->getDocumentElement();
            HTMLArray* rootelms = root->getChildNodes();
            HTMLElement* returnElm;
            for (int i = 1; i < rootelms->getLength(); i++) {
                HTMLElement* currelm = rootelms->item(i);
                char* nodeName = xercesc::XMLString::transcode(currelm->getNodeName());
                std::string str(nodeName);
                if (str == "body") {
                    xercesc::XMLString::release(&nodeName);
                    returnElm = currelm;
                    return returnElm;
                }
                xercesc::XMLString::release(&nodeName);
            }
            endHTML();
            return NULL;
        }
        HTMLText* getTitle(HTMLElement* head) {
            initHTML();
            HTMLArray* headCont = head->getChildNodes();
            for (int i = 1; i < headCont->getLength(); i++) {
                HTMLElement* currelm = headCont->item(i);
                char* nodeName = xercesc::XMLString::transcode(currelm->getNodeName());
                std::string str(nodeName);
                if (str == "title") {
                    xercesc::XMLString::release(&nodeName);
                    return xercesc::XMLString::transcode(currelm->getTextContent());
                }
                xercesc::XMLString::release(&nodeName);
            }
            endHTML();
            return NULL;
        }
        AHTMLArray getElementsByTagName(HTMLElement* body, HTMLText* search) {
            initHTML();
            HTMLArray* elms = body->getChildNodes();
            AHTMLArray result;
            for (int i = 1; i < elms->getLength(); i++) {
                HTMLElement* elm = elms->item(i);
                char* nodeName = xercesc::XMLString::transcode(elm->getNodeName());
                std::string str(nodeName);
                if (str == search) {
                    result.push_back(elm);
                }
            }
            endHTML();
            return result;
        }
        std::string* getText(HTMLElement* elm) {
            std::string str(xercesc::XMLString::transcode(elm->getTextContent()));
            return str;
        }
        void walkDOM(HTMLElement* start, std::function<void(HTMLElement*)> callback) {
            if (start->hasChildNodes() == true) {
                HTMLArray* elms = start->getChildNodes();
                HTMLElement* curr;
                for (int i = 1; i < elms->getLength(); i++) {
                    curr = elms->item(i);
                    if (curr->hasChildNodes() == true) {
                        MK::HTML::walkDOM(curr, callback);
                    }
                    callback(curr);
                }
            }
        }
        std::string type(HTMLElement* elm) {
            char* nodeName = xercesc::XMLString::transcode(elm->getNodeName());
            std::string str(nodeName);
            return str;
        }
        const HTMLText* ctype(HTMLElement* elm) {
            char* nodeName = xercesc::XMLString::transcode(elm->getNodeName());
            std::string str(nodeName);
            return str.c_str();
        }
    };
    HTMLText* toText(const XMLCh* text) {
        return xercesc::XMLString::transcode(text);
    }
    void release(HTMLText* item) {
        initHTML();
        xercesc::XMLString::release(&item);
        endHTML();
    }
}
