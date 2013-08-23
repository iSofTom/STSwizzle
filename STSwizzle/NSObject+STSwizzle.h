//
//  NSObject+STSwizzle.h
//  STSwizzle
//
//  Created by Thomas Dupont on 22/08/13.

/***********************************************************************************
 *
 * Copyright (c) 2013 Thomas Dupont
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ***********************************************************************************/

#import <Foundation/Foundation.h>

@interface NSObject (STSwizzle)

typedef id implementation_block;

/*
 *	@brief	Method to swizzle implementations of two instance methods of the same class
 *			You can execute the implementation of the first method by calling the second method, and vice versa
 *	@param	firstSelector the selector of the first method
 *	@param	secondSelector the selector of the second method
 */
+ (void)swizzleInstanceMethod:(SEL)firstSelector withMethod:(SEL)secondSelector;

/*
 *	@brief	Method to swizzle implementations of two instance methods of two classes
 *			You can execute the implementation of the first method by calling the second method, and vice versa
 *	@param	firstSelector the selector of the first method
 *	@param	secondSelector the selector of the second method
 *	@param	secondClass the class of the second method
 */
+ (void)swizzleInstanceMethod:(SEL)firstSelector withMethod:(SEL)secondSelector inClass:(Class)secondClass;

/*
 *	@brief	Method to swizzle implementations of two class methods of the same classes
 *			You can execute the implementation of the first method by calling the second method, and vice versa
 *	@param	firstSelector the selector of the first method
 *	@param	secondSelector the selector of the second method
 */
+ (void)swizzleClassMethod:(SEL)firstSelector withMethod:(SEL)secondSelector;

/*
 *	@brief	Method to swizzle implementations of two class methods of two classes
 *			You can execute the implementation of the first method by calling the second method, and vice versa
 *	@param	firstSelector the selector of the first method
 *	@param	secondSelector the selector of the second method
 *	@param	secondClass the class of the second method
 */
+ (void)swizzleClassMethod:(SEL)firstSelector withMethod:(SEL)secondSelector inClass:(Class)c;

/*
 *	@brief	Method to add a method on an object at runtime
 *          Warning: this method works only in debug mode !
 *          If a method exists for the given selector, its implementation will not be replaced !
 *	@param	selector the selector for which you want to set an implementation
 *	@param	types the types of the parameters
 *			first character is return type (for example "v" for void return)
 *			second is "@" for self
 *			third is ":" for cmd
 *			then there is a character for each parameter (for example "i" for an int, "@" for an object, ...)
 *			for all available character, see https://developer.apple.com/library/mac/#documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html
 *	@param	impl the new implementation in a block.
 *			the block takes several parameters, first is an id representing self.
 *			next parameters are all the parameters of the method.
 *
 *	example:
 *			[toto addForSelector:@selector(logInt:)
 *						   types:"v@:i"
 *				  implementation:^(int i) {
 *					NSLog(@"int %i", i);
 *				  }];
 */
- (void)addMethodForSelector:(SEL)selector types:(char*)types implementation:(implementation_block)impl;

/*
 *	@brief	Method to replace an implementation at runtime
 *          Warning: this method works only in debug mode !
 *	@param	selector the selector for which you want to change the implementation
 *	@param	impl the new implementation in a block.
 *			the block takes several parameters, first is an id representing self.
 *			next parameters are all the parameters of the method.
 *
 *	example:
 *			[myVC replaceMethodForSelector:@selector(shouldAutorotateToInterfaceOrientation:)
 *							implementation:^(id _self, UIInterfaceOrientation orientation) {
 *											return UIInterfaceOrientationIsLandscape(orientation);
 *							}];
 */
- (void)replaceMethodForSelector:(SEL)selector implementation:(implementation_block)impl;

/*
 *	@brief	Method to call the original implementation when you replace the implementation for a selector
 *          Warning: If the method is called during the block execution, only the original implementation will be called !
 *
 *	example:
 *			[toto replaceMethodForSelector:@selector(foo)
 *							implementation:^(id _self) {
 *								//do something
 *								[_self callOnSuper:^{
 *									[_self foo];
 *								}];
 *							}];
 */
- (void)callOnSuper:(dispatch_block_t)block;

/*
 *	@brief  Method to rollback to the original implementation
 *          Both addMethodForSelector:types:implementation and replaceMethodForSelector:implementation: methods will be rollback !
 */
- (void)rollbackMethodReplacements;

@end
