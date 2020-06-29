#ROS2 import
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

#Our toolbox
from .com import Uart

RATE = 0.001

class SerialReceiver(Node):
    def __init__(self):
        super().__init__('serial_receiver')
        self.serial_com = Uart('emulatorRX', '/dev/ttyTHS1', 1000000)
        self.publisher_ = self.create_publisher(String, 'emulatorReceive', 10)
        self.timer = self.create_timer(RATE, self.timer_callback)

    #def listener_callback(self, msg):
    #    self.get_logger().info('Serial out: {}'.format(msg.data))
    #    self.serial_com.write_line(msg.data.encode())

    def timer_callback(self):
        msg = String()
        msg.data = self.serial_com.get_line()
        self.publisher_.publish(msg)
        self.get_logger().info('Receive: "%s"' % msg.data)

def main(args=None):
    rclpy.init(args=args)

    serial_receiver = SerialReceiver()

    rclpy.spin(serial_receiver)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    serial_receiver.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
