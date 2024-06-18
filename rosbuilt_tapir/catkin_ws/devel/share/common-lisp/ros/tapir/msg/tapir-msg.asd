
(cl:in-package :asdf)

(defsystem "tapir-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "VrepInfo" :depends-on ("_package_VrepInfo"))
    (:file "_package_VrepInfo" :depends-on ("_package"))
  ))