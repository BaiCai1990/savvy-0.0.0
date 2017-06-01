; Auto-generated. Do not edit!


(cl:in-package savvy-msg)


;//! \htmlinclude fourvel.msg.html

(cl:defclass <fourvel> (roslisp-msg-protocol:ros-message)
  ((n1
    :reader n1
    :initarg :n1
    :type cl:integer
    :initform 0)
   (n2
    :reader n2
    :initarg :n2
    :type cl:integer
    :initform 0)
   (n3
    :reader n3
    :initarg :n3
    :type cl:integer
    :initform 0)
   (n4
    :reader n4
    :initarg :n4
    :type cl:integer
    :initform 0))
)

(cl:defclass fourvel (<fourvel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <fourvel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'fourvel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name savvy-msg:<fourvel> is deprecated: use savvy-msg:fourvel instead.")))

(cl:ensure-generic-function 'n1-val :lambda-list '(m))
(cl:defmethod n1-val ((m <fourvel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:n1-val is deprecated.  Use savvy-msg:n1 instead.")
  (n1 m))

(cl:ensure-generic-function 'n2-val :lambda-list '(m))
(cl:defmethod n2-val ((m <fourvel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:n2-val is deprecated.  Use savvy-msg:n2 instead.")
  (n2 m))

(cl:ensure-generic-function 'n3-val :lambda-list '(m))
(cl:defmethod n3-val ((m <fourvel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:n3-val is deprecated.  Use savvy-msg:n3 instead.")
  (n3 m))

(cl:ensure-generic-function 'n4-val :lambda-list '(m))
(cl:defmethod n4-val ((m <fourvel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader savvy-msg:n4-val is deprecated.  Use savvy-msg:n4 instead.")
  (n4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <fourvel>) ostream)
  "Serializes a message object of type '<fourvel>"
  (cl:let* ((signed (cl:slot-value msg 'n1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'n2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'n3)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'n4)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <fourvel>) istream)
  "Deserializes a message object of type '<fourvel>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n3) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n4) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<fourvel>)))
  "Returns string type for a message object of type '<fourvel>"
  "savvy/fourvel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'fourvel)))
  "Returns string type for a message object of type 'fourvel"
  "savvy/fourvel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<fourvel>)))
  "Returns md5sum for a message object of type '<fourvel>"
  "95e8630f1e0146dada81638c9731ebd8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'fourvel)))
  "Returns md5sum for a message object of type 'fourvel"
  "95e8630f1e0146dada81638c9731ebd8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<fourvel>)))
  "Returns full string definition for message of type '<fourvel>"
  (cl:format cl:nil "int32 n1~%int32 n2~%int32 n3~%int32 n4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'fourvel)))
  "Returns full string definition for message of type 'fourvel"
  (cl:format cl:nil "int32 n1~%int32 n2~%int32 n3~%int32 n4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <fourvel>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <fourvel>))
  "Converts a ROS message object to a list"
  (cl:list 'fourvel
    (cl:cons ':n1 (n1 msg))
    (cl:cons ':n2 (n2 msg))
    (cl:cons ':n3 (n3 msg))
    (cl:cons ':n4 (n4 msg))
))
