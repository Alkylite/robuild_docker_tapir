
(cl:in-package :asdf)

(defsystem "tapir-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "simRosLoadScene" :depends-on ("_package_simRosLoadScene"))
    (:file "_package_simRosLoadScene" :depends-on ("_package"))
    (:file "simRosGetObjectHandle" :depends-on ("_package_simRosGetObjectHandle"))
    (:file "_package_simRosGetObjectHandle" :depends-on ("_package"))
    (:file "simRosStopSimulation" :depends-on ("_package_simRosStopSimulation"))
    (:file "_package_simRosStopSimulation" :depends-on ("_package"))
    (:file "simRosGetObjectPose" :depends-on ("_package_simRosGetObjectPose"))
    (:file "_package_simRosGetObjectPose" :depends-on ("_package"))
    (:file "simRosStartSimulation" :depends-on ("_package_simRosStartSimulation"))
    (:file "_package_simRosStartSimulation" :depends-on ("_package"))
    (:file "simRosSetObjectPosition" :depends-on ("_package_simRosSetObjectPosition"))
    (:file "_package_simRosSetObjectPosition" :depends-on ("_package"))
    (:file "simRosCopyPasteObjects" :depends-on ("_package_simRosCopyPasteObjects"))
    (:file "_package_simRosCopyPasteObjects" :depends-on ("_package"))
  ))