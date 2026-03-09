package com.craftinginterpreters.lox;

import java.util.List;

class LoxFunction implements LoxCallable {
  private final Stmt.Function declaration;
   private final Expr.Function expression;
  private final Environment closure;
  LoxFunction(Stmt.Function declaration, Environment closure) {
    this.closure = closure;
    this.expression = null;
    this.declaration = declaration;
  }

  LoxFunction(Expr.Function expression, Environment closure) {
    this.expression = expression;
    this.declaration = null;
    this.closure = closure;
  }

  @Override
  public Object call(Interpreter interpreter,
                     List<Object> arguments) {
    Environment environment = new Environment(closure);
    List<Token> params =
    declaration != null ? declaration.params : expression.params;

    for (int i = 0; i < params.size(); i++) {
      environment.define(params.get(i).lexeme,
        arguments.get(i));
}

    try {
      List<Stmt> body =
          declaration != null ? declaration.body : expression.body;

      interpreter.executeBlock(body, environment);
    } catch (Return returnValue) {
      return returnValue.value;
    }
    return null;
  }
  
  @Override
public int arity() {
  if (declaration != null) return declaration.params.size();
  return expression.params.size();
}

  @Override
  public String toString() {
    return "<fn " + declaration.name.lexeme + ">";
  }

}