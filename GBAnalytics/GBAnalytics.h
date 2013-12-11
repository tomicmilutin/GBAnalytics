//
//  GBAnalytics.h
//  GBAnalytics
//
//  Created by Luka Mirosevic on 29/01/2013.
//  Copyright (c) 2013 Goonbee. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GBAnalyticsNetworks.h"

extern NSString * const kGBAnalyticsDefaultEventRouter;

#define GBAnalytics [GBAnalyticsManager sharedManager]

@class GBAnalyticsEventRouter;

@interface GBAnalyticsManager : NSObject

@property (assign, nonatomic, setter = setDebug:, getter = isDebugEnabled) BOOL isDebugEnabled;

+(GBAnalyticsManager *)sharedManager;

-(void)connectNetwork:(GBAnalyticsNetwork)network withCredentials:(NSString *)credentials, ...;//See GBAnalyticsNetworks.h for param list

-(void)setDebug:(BOOL)enable;
-(BOOL)isDebugEnabled;

//Allows using the square bracket syntax for choosing the event router
-(GBAnalyticsEventRouter *)objectForKeyedSubscript:(NSString *)route;

//These alias the default event router
-(void)routeToNetworks:(GBAnalyticsNetwork)network, ... NS_REQUIRES_NIL_TERMINATION;
-(void)trackEvent:(NSString *)event;
-(void)trackEvent:(NSString *)event withParameters:(NSDictionary *)parameters;

@end

@interface GBAnalyticsEventRouter : NSObject

@property (copy, nonatomic, readonly) NSString *route;

-(void)routeToNetworks:(GBAnalyticsNetwork)network, ... NS_REQUIRES_NIL_TERMINATION;
-(void)trackEvent:(NSString *)event;
-(void)trackEvent:(NSString *)event withParameters:(NSDictionary *)parameters;

@end

//Shorthands
static inline void TrackEvent(NSString *event) { [GBAnalytics trackEvent:event]; }
static inline void TrackEventWithDictionary(NSString *event, NSDictionary *parameters) { [GBAnalytics trackEvent:event withParameters:parameters]; }

//Super Shorthands
static inline void _t(NSString *event) { TrackEvent(event); }
static inline void _tp(NSString *event, NSDictionary *parameters) { TrackEventWithDictionary(event, parameters); }
