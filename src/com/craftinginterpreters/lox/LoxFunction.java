package com.craftinginterpreters.lox;

import java.util.List;

class LoxFunction implements LoxCallable {
  private final Stmt.Function declaration;
   private final Expr.Function expression;
  private final Environment closure;
  private final boolean isInitializer;

  LoxFunction(Stmt.Function declaration, Environment closure, boolean isInitializer) {
    this.isInitializer = isInitializer;
    this.closure = closure;
    this.expression = null;
    this.declaration = declaration;
  }

  LoxFunction(Expr.Function expression, Environment closure) {
    this.expression = expression;
    this.declaration = null;
    this.closure = closure;
  }

  LoxFunction bind(LoxInstance instance) {
    Environment environment = new Environment(closure);
    environment.define("this", instance);
    return new LoxFunction(declaration, environment,
                           isInitializer);
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
      if (isInitializer) return closure.getAt(0, "this");
      return returnValue.value;
    }

    if (isInitializer) return closure.getAt(0, "this");
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