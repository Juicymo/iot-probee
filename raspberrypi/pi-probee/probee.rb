require 'agens'

require_relative 'communication/I2C.rb'

# Definition
class UltrasonicSensor < Sensor
	include I2C
end

class Motor < Actuator
	include I2C
end

class MovementAgent < Agent
	def setup
		sensor UltrasonicSensor
		actuator Motor
	end
	
	def perform_reasoning
		forward
	end
end

class ProbeeMAS < MAS
	agent MovementAgent
end

# Program
mas = ExampleMAS.new
mas.run

mas.world.dump

sleep(2)

mas.shutdown