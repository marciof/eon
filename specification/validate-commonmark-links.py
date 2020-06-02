#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

# Standard:
import fileinput
from http import HTTPStatus
from html.parser import HTMLParser
import sys
from typing import Callable
from urllib.request import Request, urlopen

# External:
# TODO pure Python CommonMark parser
from paka import cmark # v2.2.0


# TODO logging?
class LinkExtractorHtmlParser (HTMLParser):
    def __init__(self, callback: Callable[[str], None]):
        super().__init__()
        self.callback = callback

    def handle_starttag(self, tag: str, attrs) -> None:
        if tag == 'a':
            for (attr_name, attr_value) in attrs:
                if attr_name == 'href':
                    self.callback(attr_value)


# TODO stream input
def slurp_input() -> str:
    return ''.join([line for line in fileinput.input()])


# TODO walk CommonMark AST instead of parsing to HTML just to get links
def convert_commonmark_to_html(commonmark: str) -> str:
    return cmark.to_html(commonmark, safe = False)


def list_html_links(html: str, callback: Callable[[str], None]) -> None:
    link_extractor = LinkExtractorHtmlParser(callback)
    link_extractor.feed(html)


# TODO report redirects?
# TODO parallelize link checking for speed
def is_link_valid(link: str) -> bool:
    if not link.startswith('http'):
        return True

    with urlopen(Request(link, method = 'HEAD')) as request:
        status_code = request.getcode()
        is_ok = status_code == HTTPStatus.OK
        stream = sys.stdout if is_ok else sys.stderr

        print(status_code, link, file = stream)
        return is_ok


# TODO documentation
# TODO tests
if __name__ == '__main__':
    has_invalid_links = {True}

    list_html_links(convert_commonmark_to_html(slurp_input()),
        callback = lambda link:
            has_invalid_links.discard(is_link_valid(link)))

    if has_invalid_links:
        sys.exit(1)