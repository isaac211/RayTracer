Put Your design decisions here. What modules you defined and how they
interact to solve the ray tracing problem.


{object,camera,light}.{cpp,hpp}
Object, Camera, and Light are all classes that store the properties of each
asset to be later retrieved for ray tracing. Each class contains get methods
for retrieving internal variables. Camera is the lowest level asset and
contains definitions and library inclusions used in other classes, such as
some typedefs and the struct that defines a 3D coordinate. Object also contains
the definition of a ray and an inline dot product function.

{sphere,plane}.{cpp,hpp}
These classes inherit from Object and define the primary shapes use for ray
tracing. The classes contain a unique member not in Object -- radius and
normal respectively. They also contain methods for calculating intersections
between a ray and it surfaces as well as s

environment.{cpp,hpp}
Environment has a camera, a vector of Spheres, a vector of Planes, and
a vector of Lights as its members. In addition to get methods, it also
contains the method for parsing a JSON file's data into its members.
For error checking, Environment also contains inline functions for
identifying doubles, floats, and integers.

ray_tracer.{cpp,hpp}
RayTracer is designed as a wrapper around Environment to parse its members
into a PNG output. It also contains the autoexposure method to constrain
RGB values between 0 and 255.

