;;;; basic-server.lisp

(in-package #:basic-server)

(defparameter *dir* (merge-pathnames "c/main" (asdf:system-source-directory :basic-server)))
(defparameter *error-res* (format nil
				  "HTTP/1.1 404 Not Found~A~AContent-Type: text/plain~A~A~A~A~A"
				  #\return #\linefeed
				  #\return #\linefeed
				  #\return #\linefeed
				  "404 not found"))


;; this doesn't work yet. TODO
(define-foreign-library c-server
  (t (:default (namestring *dir*))))

(define-foreign-library c-server
  (t (:default "/home/evan/quicklisp/local-projects/basic-server/c/main")))

(use-foreign-library c-server)

(defun server-loop (req)
  (let ((res *error-res*))
    (ignore-errors (progn
		     (format nil "Client req: ~A" req)
		     (setf res (format nil
				       "HTTP/1.1 200 OK~A~AContent-Type: text/plain~A~A~A~A~A"
				       #\return #\linefeed
				       #\return #\linefeed
				       #\return #\linefeed
				       "Hello, World!"))))
    res))

(defcallback server-loop-cb :string ((req :string))
  (server-loop req))

(defun server-start ()
  (print "Server has started."))

(defcallback server-start-cb :void ()
  (server-start))

(defun start-server (port maxbuf)
  (foreign-funcall "start_server"
		   :int port
		   :int maxbuf
		   :pointer (callback server-loop-cb)
		   :pointer (callback server-start-cb)
		   :void))

;;(start-server 8094 2024)







