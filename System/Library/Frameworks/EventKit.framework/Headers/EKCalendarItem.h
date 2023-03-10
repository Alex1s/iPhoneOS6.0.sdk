//
//  EKCalendarItem.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <EventKit/EKObject.h>
#import <EventKit/EventKitDefines.h>

@class EKRecurrenceRule, EKAlarm, EKCalendar, EKStructuredLocation;

EVENTKIT_CLASS_AVAILABLE(10_8, 5_0)
@interface EKCalendarItem : EKObject {

}

/*!
    @property   UUID
    @discussion This is now deprecated; use calendarItemIdentifier instead.
 */
@property(nonatomic, readonly) NSString *UUID __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_6_0);

@property(nonatomic, retain) EKCalendar *calendar;

/*!
    @property   calendarItemIdentifier
    @abstract   A unique identifier for a calendar item.
    @discussion Item identifiers are not sync-proof in that a full sync will lose
                this identifier, so you should always have a back up plan for dealing
                with a reminder that is no longer fetchable by this property, e.g. by title, etc.
                Use [EKEventStore calendarItemWithIdentifier:] to look up the item by this value.
*/
@property(nonatomic, readonly) NSString *calendarItemIdentifier __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @property   calendarItemExternalIdentifier
    @abstract   A server-provided identifier for this calendar item
    @discussion This identifier, provided by the server, allows you to reference the same event or reminder across
                multiple devices. For calendars stored locally on the device, including the birthday calendar,
                it simply passes through to calendarItemIdentifier.
 
                This identifier is unique as of creation for every calendar item.  However, there are some
                cases where duplicate copies of a calendar item can exist in the same database, including:
                - A calendar item was imported from an ICS file into multiple calendars
                - An event was created in a calendar shared with the user and the user was also invited to the event
                - The user is a delegate of a calendar that also has this event
                - A subscribed calendar was added to multiple accounts
                In such cases, you should choose between calendar items based on other factors, such as
                the calendar or source.
             
                This identifier is the same for all occurrences of a recurring event. If you wish to differentiate
                between occurrences, you may want to use the start date.
 
                In addition, there are two caveats for Exchange-based calendars:
                - This identifier will be different between EventKit on iOS versus OS X
                - This identifier will be different between devices for EKReminders
*/
@property(nonatomic, readonly) NSString *calendarItemExternalIdentifier __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

@property(nonatomic, copy) NSString *title;
@property(nonatomic, copy) NSString *location;
@property(nonatomic, copy) NSString *notes;
@property(nonatomic, copy) NSURL *URL __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

@property(nonatomic, readonly) NSDate *lastModifiedDate;
@property(nonatomic, readonly) NSDate *creationDate __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0); // might be nil
@property(nonatomic, copy) NSTimeZone *timeZone  __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

// These exist to do simple checks for the presence of data without
// loading said data. While at present only hasRecurrenceRules has a
// fast path, it is a good idea to use these if you only need to know
// the data exists anyway since at some point they will all be a
// simple check.
@property(nonatomic, readonly) BOOL hasAlarms  __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);
@property(nonatomic, readonly) BOOL hasRecurrenceRules  __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);
@property(nonatomic, readonly) BOOL hasAttendees  __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);
@property(nonatomic, readonly) BOOL hasNotes  __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

// An array of EKParticipant objects
@property(nonatomic, readonly) NSArray *attendees;

// An array of EKAlarm objects
@property(nonatomic, copy) NSArray *alarms;

/*!
    @method     addAlarm:
    @abstract   Adds an alarm to this item.
    @discussion This method add an alarm to an item. Be warned that some calendars can only
                allow a certain maximum number of alarms. When this item is saved, it will
                truncate any extra alarms from the array.
*/
- (void)addAlarm:(EKAlarm *)alarm;

/*!
    @method     removeAlarm:
    @abstract   Removes an alarm from this item.
*/
- (void)removeAlarm:(EKAlarm *)alarm;


/*!
    @property   recurrenceRules
    @abstract   An array of EKRecurrenceRules, or nil if none.
*/
@property(nonatomic, copy) NSArray *recurrenceRules __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

- (void)addRecurrenceRule:(EKRecurrenceRule *)rule;
- (void)removeRecurrenceRule:(EKRecurrenceRule *)rule;

@end
