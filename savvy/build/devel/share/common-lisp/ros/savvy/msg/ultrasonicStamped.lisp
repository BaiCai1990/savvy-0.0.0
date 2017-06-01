; Auto-generated. Do not edit!


(cl:in-package savvy-msg)


;//! \htmlinclude ultrasonicStamped.msg.html

(cl:defclass <ultrasonicStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (d1
    :reader d1
    :initarg :d1
    :type cl:fixnum
    :initform 0)
   (d2
    :reader d2
    :initarg :d2
    :type cl:fixnum
    :initform 0)
   (d3
    :reader d3
    :initarg :d3
    :type cl:fixnum
    :initform 0)
   (d4
    :reader d4
    :initarg :d4
    :type cl:fixnum
    :initform 0)
   (d5
    :reader d5
    :initarg :d5
    :type cl:fixnum
    :initform 0)
   (d6
    :reader d6
    :initarg :d6
    :type cl:fixnum
    :initform 0))
)

(cl:defclass ultrasonicStamped (<ultrasonicStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ultrasonicStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ultrasonicStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name savvy-msg:<ultrasonicStamped> is deprecated: use savvy-msg:ultrasonicStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:header-val is deprecated.  Use savvy-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'd1-val :lambda-list '(m))
(cl:defmethod d1-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:d1-val is deprecated.  Use savvy-msg:d1 instead.")
  (d1 m))

(cl:ensure-generic-function 'd2-val :lambda-list '(m))
(cl:defmethod d2-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:d2-val is deprecated.  Use savvy-msg:d2 instead.")
  (d2 m))

(cl:ensure-generic-function 'd3-val :lambda-list '(m))
(cl:defmethod d3-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:d3-val is deprecated.  Use savvy-msg:d3 instead.")
  (d3 m))

(cl:ensure-generic-function 'd4-val :lambda-list '(m))
(cl:defmethod d4-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:d4-val is deprecated.  Use savvy-msg:d4 instead.")
  (d4 m))

(cl:ensure-generic-function 'd5-val :lambda-list '(m))
(cl:defmethod d5-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:d5-val is deprecated.  Use savvy-msg:d5 instead.")
  (d5 m))

(cl:ensure-generic-function 'd6-val :lambda-list '(m))
(cl:defmethod d6-val ((m <ultrasonicStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:d6-val is deprecated.  Use savvy-msg:d6 instead.")
  (d6 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ultrasonicStamped>) ostream)
  "Serializes a message object of type '<ultrasonicStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd4)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd4)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd5)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd5)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd6)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd6)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ultrasonicStamped>) istream)
  "Deserializes a message object of type '<ultrasonicStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd4)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd4)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd5)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd5)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'd6)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'd6)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ultrasonicStamped>)))
  "Returns string type for a message object of type '<ultrasonicStamped>"
  "savvy/ultrasonicStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ultrasonicStamped)))
  "Returns string type for a message object of type 'ultrasonicStamped"
  "savvy/ultrasonicStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ultrasonicStamped>)))
  "Returns md5sum for a message object of type '<ultrasonicStamped>"
  "521b9ed7342a78d6b1ce59a46ac3eb57")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ultrasonicStamped)))
  "Returns md5sum for a message object of type 'ultrasonicStamped"
  "521b9ed7342a78d6b1ce59a46ac3eb57")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ultrasonicStamped>)))
  "Returns full string definition for message of type '<ultrasonicStamped>"
  (cl:format cl:nil "Header header~%uint16 d1~%uint16 d2~%uint16 d3~%uint16 d4~%uint16 d5~%uint16 d6~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ultrasonicStamped)))
  "Returns full string definition for message of type 'ultrasonicStamped"
  (cl:format cl:nil "Header header~%uint16 d1~%uint16 d2~%uint16 d3~%uint16 d4~%uint16 d5~%uint16 d6~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ultrasonicStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     2
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ultrasonicStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'ultrasonicStamped
    (cl:cons ':header (header msg))
    (cl:cons ':d1 (d1 msg))
    (cl:cons ':d2 (d2 msg))
    (cl:cons ':d3 (d3 msg))
    (cl:cons ':d4 (d4 msg))
    (cl:cons ':d5 (d5 msg))
    (cl:cons ':d6 (d6 msg))
))
