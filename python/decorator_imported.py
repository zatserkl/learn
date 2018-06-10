# See Answer #21 from
# https://stackoverflow.com/questions/25829364/applying-a-decorator-to-an-imported-function

# Decorators are just syntactic sugar to replace a function object with a
# decorated version, where decorating is just calling (passing in the original
# function object). In other words, the syntax:
# 
#   @decorator_expression
#   def function_name():
#       # function body
#
#   translates to:
#   
#   def function_name():
#       # function body
#
#   function_name = decorator_expression(function_name)
#
#   In your case, you can apply your decorator manually instead:
#   
#   from random import randint
#   
#   randint = decorator(randint)
#
#   NB: It's a good idea to use @wraps(func) in decorator
