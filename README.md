STSwizzle
=========

STSwizzle add several methods on NSObject.
Some methods allows to swizzle methods on a class, others to swizzle methods for a particular instance.

If you are wondering, swizzle is a way to exchange the instructions that will be executed when a method is called.

## Swizzle on a class

```
+ (void)swizzleClassMethod:(SEL)firstSelector withMethod:(SEL)secondSelector;
```

This method allow you to swizzle two class methods. For example you can swizzle `+(void)foo1` and `+(void)foo2` so that when the foo1 method is called, the foo2 function is executed, and vice versa.

```
+ (void)swizzleInstanceMethod:(SEL)firstSelector withMethod:(SEL)secondSelector;
```

This method allow to swizzle two instance methods. those methods will be swizzle for all the instances of the class.

## Swizzle on an instance

```
- (void)addMethodForSelector:(SEL)selector types:(char*)types implementation:(implementation_block)impl;
```

This method allow to add a new method to an instance. When the selector passed in parameters is called on that instance, the implementation block in parameters is executed.

```
- (void)replaceMethodForSelector:(SEL)selector implementation:(implementation_block)impl;
```

This method allow to replace a method on an instance. When the selector passed in parameters is called on that instance, the implementation block in parameters is instead executed.

## Installation

To include this component in your project, I recommend you to use [Cocoapods](http://cocoapods.org):
* Add `pod "STSwizzle"` to your Podfile.

## How does it work ?

_An article about swizzling will be soon available_.