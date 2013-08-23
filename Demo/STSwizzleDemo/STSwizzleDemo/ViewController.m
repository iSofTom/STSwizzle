//
//  ViewController.m
//  STSwizzleDemo
//
//  Created by Thomas Dupont on 22/08/13.
//  Copyright (c) 2013 iSofTom. All rights reserved.
//

#import "ViewController.h"

#import "NSObject+STSwizzle.h"
#import <objc/runtime.h>

@interface ViewController ()

@end

@implementation ViewController

- (IBAction)handleAddMethodButtonTap:(id)sender
{
    [self addMethodForSelector:@selector(keepCalm) types:"v@:" implementation:^(id _self){
        NSLog(@"Keep Calm");
    }];
	
    // When I call the keepCalm method, the hereabove block will be executed
    [self performSelector:@selector(keepCalm)];
    
    
    [self rollbackMethodReplacements];
    
    // After the rollback, the method does not exist anymore.
    // Calling the method could raise an Unrecognized selector exception but thanks to the forwarding mechanism I prevent the demo to crash
    // If you want to learn more about the forwarding mechanism, see http://www.isoftom.com/2013/08/forwarding-mechanism.html
    [self performSelector:@selector(keepCalm)];
}



- (IBAction)handleReplaceMethodButtonTap:(id)sender
{
    // Here when I call the starbuck method, it returns the NSString @"Starbuck"
    NSLog(@"%@", [self starbuck]);
    
    
    [self replaceMethodForSelector:@selector(starbuck) implementation:^(id _self){
        return [NSString stringWithFormat:@"Kara Thrace is Starbuck"];
    }];
    
    // But now that I replaced the method, it returns an other NSString !
    NSLog(@"%@", [self starbuck]);
    
    
    [self replaceMethodForSelector:@selector(starbuck) implementation:^(id _self){
        __block NSString* starbuck = nil;
        [_self callOnSuper:^{
            starbuck = [_self starbuck];
        }];
        return [NSString stringWithFormat:@"Katee Sackhoff is %@", starbuck];
    }];
    
    // I can even call the old implementation from the new one !
    NSLog(@"%@", [self starbuck]);
}

- (NSString*)starbuck
{
    return @"Starbuck";
}



- (IBAction)handleSwizzleButtonTap:(id)sender
{
    [ViewController swizzleInstanceMethod:@selector(jekyll) withMethod:@selector(hyde)];
    
    [self jekyll];
}

- (void)jekyll
{
    NSLog(@"Jekyll");
}

- (void)hyde
{
    NSLog(@"Hyde");
}

#pragma mark - Prevent unrecognized selector exception

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    if (sel_isEqual(aSelector, @selector(keepCalm)))
    {
        return [NSMethodSignature signatureWithObjCTypes:"v@:"];
    }
    
    return nil;
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    if (sel_isEqual(anInvocation.selector, @selector(keepCalm)))
    {
        NSLog(@"And call the Doctor");
    }
    else
    {
        NSLog(@"unrecognized selector %@", NSStringFromSelector(anInvocation.selector));
    }
}

@end
