private void blockComment() {
  while (!isAtEnd()) {
    if (peek() == '\n') line++;

    // Look for closing */
    if (peek() == '*' && peekNext() == '/') {
      advance(); // '*'
      advance(); // '/'
      return;
    }

    advance();
  }

  Lox.error(line, "Unterminated block comment");
}