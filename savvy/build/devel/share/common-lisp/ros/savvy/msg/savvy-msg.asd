
(cl:in-package :asdf)

(defsystem "savvy-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "fourvel" :depends-on ("_package_fourvel"))
    (:file "_package_fourvel" :depends-on ("_package"))
    (:file "ultrasonicStamped" :depends-on ("_package_ultrasonicStamped"))
    (:file "_package_ultrasonicStamped" :depends-on ("_package"))
  ))