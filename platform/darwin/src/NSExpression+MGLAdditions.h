#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
    #import <UIKit/UIKit.h>
#else
    #import <Cocoa/Cocoa.h>
#endif

#import "MGLTypes.h"

NS_ASSUME_NONNULL_BEGIN

typedef NSString *MGLExpressionStyleFunction NS_STRING_ENUM;
typedef NSString *MGLExpressionInterpolationMode NS_STRING_ENUM;

/**
 An `NSString` identifying the `zoomLevel` operator in an `NSExpression`.
 
 This attribute corresponds to the
 <a href="https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions-zoom"><code>zoom</code></a>
 expression reference in the Mapbox Style Specification.
 */
extern MGL_EXPORT const MGLExpressionStyleFunction MGLExpressionStyleFunctionZoomLevel;

/**
 An `NSString` identifying the `heatmapDensity` operator in an `NSExpression`.
 
 This attribute corresponds to the
 <a href="https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions-heatmap-density"><code>heatmap-density</code></a>
 expression reference in the Mapbox Style Specification.
 */
extern MGL_EXPORT const MGLExpressionStyleFunction MGLExpressionStyleFunctionHeatmapDensity;

/**
 An `NSString` identifying the `linear` interpolation type in an `NSExpression`.
 
 This attribute corresponds to the `linear` value in the
 <a href="https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions-interpolate"><code>interpolate</code></a>
 expression reference in the Mapbox Style Specification.
 */
extern MGL_EXPORT const MGLExpressionInterpolationMode MGLExpressionInterpolationModeLinear;

/**
 An `NSString` identifying the `expotential` interpolation type in an `NSExpression`.
 
 This attribute corresponds to the `exponential` value in the
 <a href="https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions-interpolate"><code>interpolate</code></a>
 expression reference in the Mapbox Style Specification.
 */
extern MGL_EXPORT const MGLExpressionInterpolationMode MGLExpressionInterpolationModeExponential;

/**
 An `NSString` identifying the `cubic-bezier` interpolation type in an `NSExpression`.
 
 This attribute corresponds to the `cubic-bezier` value in the
 <a href="https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions-interpolate"><code>interpolate</code></a>
 expression reference in the Mapbox Style Specification.
 */
extern MGL_EXPORT const MGLExpressionInterpolationMode MGLExpressionInterpolationModeCubicBezier;

@interface NSExpression (MGLAdditions)

/**
 Returns an expression equivalent to the given Foundation object deserialized
 from JSON data.
 
 The Foundation object is interpreted according to the
 [Mapbox Style Specification](https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions).
 See the
 “[Information for Style Authors](../for-style-authors.html#setting-attribute-values)”
 guide for a correspondence of operators and types between the style
 specification and the `NSExpression` representation used by this SDK.
 
 @param object A Foundation object deserialized from JSON data, for example
    using `NSJSONSerialization`.
 @return An initialized expression equivalent to `object`, suitable for use as
    the value of a style layer attribute.
 */
+ (instancetype)expressionWithMGLJSONObject:(id)object NS_SWIFT_NAME(init(mglJSONObject:));

/**
 An equivalent Foundation object that can be serialized as JSON.
 
 The Foundation object conforms to the
 [Mapbox Style Specification](https://www.mapbox.com/mapbox-gl-js/style-spec/#expressions).
 See the
 “[Information for Style Authors](../for-style-authors.html#setting-attribute-values)”
 guide for a correspondence of operators and types between the style
 specification and the `NSExpression` representation used by this SDK.
 
 You can use `NSJSONSerialization` to serialize the Foundation object as data to
 write to a file.
 */
@property (nonatomic, readonly) id mgl_jsonExpressionObject;

/**
 Returns a constant expression containing an `NSString`.
 
 This is equivalent to call `[NSExpression expressionForConstant:]`.
 
 @param string The string constant.
 */
+ (instancetype)mgl_expressionForString:(nonnull NSString *)string;

/**
 Returns a constant expression containing an `MGLColor`.
 
 This is equivalent to call `[NSExpression expressionForConstant:]`.
 
 @param color The color constant.
 */
+ (instancetype)mgl_expressionForColor:(nonnull MGLColor *)color;

/**
 Returns a constant expression containing an `NSValue`.
 
 This is equivalent to call `[NSExpression expressionForConstant:]`.
 
 @param value The value constant.
 */
+ (instancetype)mgl_expressionForValue:(nonnull NSValue *)value;

+ (instancetype)mgl_expressionForTernaryFunction:(nonnull NSString *)conditionString trueExpression:(nonnull NSExpression *)trueExpression falseExpresssion:(nonnull NSExpression *)falseExpression;

/**
 Returns a step function expression specifying the function operator, default value
 and stops.
 
 @param function The operator type in which this expression is applied.
 @param value The default value can be boolean or numeric.
 @param stops The stops dictionay must be numeric literals in strictly ascending order.
 */
+ (instancetype)mgl_expressionForStepFunction:(nonnull MGLExpressionStyleFunction)function defaultValue:(nonnull NSValue *)value stops:(nonnull NS_DICTIONARY_OF(NSNumber *, id) *)stops;

/**
 Returns a step function expression specifying the function operator, default color
 and stops.
 
 @param function The operator type in which this expression is applied.
 @param color The default color.
 @param stops The stops dictionay must be numeric literals in strictly ascending order.
 */
+ (instancetype)mgl_expressionForStepFunction:(nonnull MGLExpressionStyleFunction)function defaultColor:(nonnull MGLColor *)color stops:(nonnull NS_DICTIONARY_OF(NSNumber *, id) *)stops;

/**
 Returns a step function expression specifying the function operator, default expression
 and stops.
 
 @param function The operator type in which this expression is applied.
 @param expression The expression which could be a constant or function expression.
 @param stops The stops dictionay must be numeric literals in strictly ascending order.
 */
+ (instancetype)mgl_expressionForStepFunction:(nonnull MGLExpressionStyleFunction)function defaultExpression:(nonnull NSExpression *)expression stops:(nonnull NS_DICTIONARY_OF(NSNumber *, id) *)stops;

/**
 Returns an interpolated function expression specifying the function operator, curve type
 and steps.
 
 @param function The operator type in which this expression is applied.
 @param curveType The curve type could be `MGLExpressionInterpolationModeLinear`,
                    `MGLExpressionInterpolationModeExponential` and
                    `MGLExpressionInterpolationModeCubicBezier`.
 @param steps The stops dictionay must be numeric literals in strictly ascending order.
 */
+ (instancetype)mgl_expressionForInterpolateFunction:(nonnull MGLExpressionStyleFunction)function curveType:(nonnull MGLExpressionInterpolationMode)curveType steps:(nonnull NS_DICTIONARY_OF(NSNumber *, id) *)steps;

/**
 Returns an interpolated function expression specifying the function operator, curve type,
 parameters and steps.
 
 @param function The operator type in which this expression is applied.
 @param curveType The curve type could be `MGLExpressionInterpolationModeLinear`,
 `MGLExpressionInterpolationModeExponential` and
 `MGLExpressionInterpolationModeCubicBezier`.
 @param parameters The parameters expression.
 @param steps The stops dictionay must be numeric literals in strictly ascending order.
 */
+ (instancetype)mgl_expressionForInterpolateFunction:(nonnull MGLExpressionStyleFunction)function curveType:(nonnull MGLExpressionInterpolationMode)curveType parameters:(nullable NSExpression *)parameters steps:(nonnull NS_DICTIONARY_OF(NSNumber *, id) *)steps;

/**
 Returns a string constant expression appending the passed string.
 
 @param string The string to append.
 */
- (instancetype)mgl_appendingString:(NSString *)string;

/**
 Returns a string constant expression appending the passed expression.
 
 @param expression The evaluated expression must return a string.
 */
- (instancetype)mgl_appendingExpression:(NSExpression *)expression;


@end

NS_ASSUME_NONNULL_END
