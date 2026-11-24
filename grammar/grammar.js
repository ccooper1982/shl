function commaSep1(rule) {
  return seq(rule, repeat(seq(",", rule)));
}

export default grammar({
  name: "shl",

  extras: $ => [
    /\s/,
    $.comment,
  ],

  rules: {

    source_file: ($) => repeat(choice(
      $.function_def,
      $.statement,
    )),

    comment: $ => token(choice(
      seq("#", /[^\r\n]*/),
      seq("/#", /([^#]|#+[^#/])*#\//),
    )),

    function_def: ($) =>
      seq(
        "fn",
        field("name", $.identifier),
        "(",
        optional(field("parameters", $.parameters)),
        ")",
        optional(field("return_type", $.return_type)),
        field("body", $.block),
      ),

    parameters: ($) =>
      seq($.parameter,
        repeat(seq(",", $.parameter))),

    parameter: ($) =>
      seq(
        field("name", $.identifier),
        ":",
        optional(field("ref", $.ref_modifier)),
        field("type", $.type_name),
      ),
    type_name: ($) =>
      seq(
        $.identifier,
        optional(seq("[", "]")),
      ),
    ref_modifier: ($) => "ref",
    return_type: ($) => seq("->", field("type_name", $.type_name)),
    identifier: ($) => /[a-zA-Z_][a-zA-Z0-9_]*/,
    integer: ($) => /[0-9]+/,
    decimal: ($) => /[0-9]+\.[0-9]+/,
    boolean: ($) => choice("true","false",),
    string: ($) => /"([^"\\]|\\.)*"/,
    array_literal: ($) =>
      seq(
        "[",
        optional(seq(
          commaSep1($.expression),
          optional(","),
        )),
        "]",
      ),
    index_expression: ($) =>
      seq(
        field("array", $.identifier),
        "[",
        field("index", $.expression),
        "]",
      ),

    block: ($) => seq(
      "{",
      repeat($.statement),
      "}",
    ),

    statement: ($) =>
      choice(
        seq(
          choice(
            field("func_call", $.function_call),
            field("var_decl", $.var_decl),
            field("var_assign", $.var_assign),
            field("return", $.return),
            field("increment", $.increment_statement),
          ),
          ";"
        ),
        field("condition_if", $.condition_if),
        field("loop_while", $.loop_while),
        field("loop_for_each", $.loop_for_each),
      ),

    function_call: ($) => seq(
      field("name", $.qualified_name),
      "(",
      optional(field("args", $.arguments)),
      ")",
    ),

    arguments: ($) =>
      seq(
        $.argument,
        repeat(seq(",", $.argument)),
      ),

    argument: ($) =>
      seq(
        optional(field("ref", $.ref_modifier)),
        field("expression", $.expression),
      ),

    condition_if: ($) =>
      seq(
        "if", "(",
        field("condition", $.expression),
        ")",
        field("body", $.block),
        repeat($.else_if_clause),
        optional($.else_clause),
      ),

    return: ($) =>
      seq("return",
          optional(field("expression", $.expression))
      ),

    else_if_clause: ($) =>
      seq(
        "else", "if", "(",
        field("condition", $.expression),
        ")",
        field("body", $.block),
      ),

    else_clause: ($) =>
      seq(
        "else",
        field("body", $.block),
      ),

    loop_while: ($) =>
      seq(
        "while", "(",
        field("condition", $.expression),
        ")",
        field("body", $.block),
      ),

    loop_for_each: ($) =>
      seq(
        "for",
        "(",
        field("variable", $.identifier),
        "in",
        field("iterable", $.expression),
        ")",
        field("body", $.block),
      ),

    var_decl: ($) =>
      seq(
        field("name", $.identifier),
        choice(
          seq(
            ":",
            field("type_name", $.type_name),
            optional(seq(
              "=",
              field("initialiser", $.expression),
            )),
          ),
          seq(
            ":=",
            field("initialiser", $.expression),
          ),
        ),
      ),

    var_assign: ($) =>
      seq(
        field("name", $.identifier),
        "=",
        field("value", $.expression),
    ),

    qualified_name: ($) => seq(
      optional(seq($.identifier, "::")),
      $.identifier,
    ),

    expression: ($) => choice(
      $.decimal,
      $.integer,
      $.string,
      $.boolean,
      $.array_literal,
      $.function_call,
      $.index_expression,
      $.identifier,
      $.unary_expression,
      $.binary_expression,
      $.parenthesized_expression,
    ),

    unary_expression: $ =>
      prec.right(10, seq(
        field("op", choice("-", "!", "~", "++", "--")),
        field("expr", $.expression)
    )),

    binary_expression: ($) => choice(
        prec.left(8, seq(
            field("lhs", $.expression),
            field("op", choice("*", "/")),
            field("rhs", $.expression),
        )),

        prec.left(7, seq(
            field("lhs", $.expression),
            field("op", choice("+", "-")),
            field("rhs", $.expression),
        )),

        prec.left(6, seq(
            field("lhs", $.expression),
            field("op", choice(">", "<", ">=", "<=")),
            field("rhs", $.expression),
        )),

        prec.left(5, seq(
            field("lhs", $.expression),
            field("op", choice("==", "!=")),
            field("rhs", $.expression),
        )),

        prec.left(4, seq(
            field("lhs", $.expression),
            field("op", "|"),
            field("rhs", $.expression),
        )),

        prec.left(3, seq(
            field("lhs", $.expression),
            field("op", "&&"),
            field("rhs", $.expression),
        )),

        prec.left(2, seq(
            field("lhs", $.expression),
            field("op", "||"),
            field("rhs", $.expression),
        )),
    ),

    parenthesized_expression: ($) =>
      seq("(", $.expression, ")"),

    increment_statement: ($) =>
        field("expr", $.unary_expression),
  },
});
