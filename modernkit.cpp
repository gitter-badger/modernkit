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
#include "typecode.h"
#include "mk.cpp"

int main(int argc, char* argv[]) {
	initHTML();
  if (argc >= 2) {
		HTMLElement* head;
		HTMLElement* body;
    Parser* html = parseHTML(openFile(argv[1]));
    HTMLDocument* doc = html->getDocument();
		head = MK::HTML::getHead(doc);
		body = MK::HTML::getBody(doc);
		std::cout << MK::HTML::getTitle(head) << std::endl;
		AHTMLArray ps = MK::HTML::getElementsByTagName(body, "p");
		for (int i = 0; i < ps.size(); i++) {
			HTMLElement* elm = ps[i];
			std::cout << MK::HTML::getText(elm) << std::endl;
		}
		doc->release();
  }
	endHTML();
  return 0;
}
