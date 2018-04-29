;;;; basic-server.asd

(asdf:defsystem #:basic-server
  :description "Describe basic-server here"
  :author "Your Name <your.name@example.com>"
  :license  "Specify license here"
  :version "0.0.1"
  :serial t
  :depends-on (#:cffi)
  :components ((:file "package")
               (:file "basic-server")))
