import random
import string
from PIL import Image, ImageDraw, ImageFont, ImageFilter

def generate_captcha_text(length=6):
    """Generates random text for CAPTCHA."""
    chars = string.ascii_uppercase + string.digits
    return ''.join(random.choices(chars, k=length))

def generate_captcha_image(text, width=200, height=70):
    """Generates CAPTCHA image from text."""
    image = Image.new('RGB', (width, height), (255, 255, 255))
    # font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 40)
    font = ImageFont.truetype("C:\\Windows\\Fonts\\arialbd.ttf", 40)
    draw = ImageDraw.Draw(image)

    # Draw random lines for added complexity
    for _ in range(5):
        start = (random.randint(0, width), random.randint(0, height))
        end = (random.randint(0, width), random.randint(0, height))
        draw.line([start, end], fill=(0, 0, 0), width=2)

    # Draw the text with random positions and colors
    for i, char in enumerate(text):
        x = 30 + i * 25
        y = random.randint(5, 20)
        draw.text((x, y), char, font=font, fill=(random.randint(0, 150), 0, 0))

    # Apply filters to make it harder for bots
    image = image.filter(ImageFilter.EDGE_ENHANCE_MORE)
    return image

def main():
    captcha_text = generate_captcha_text()
    image = generate_captcha_image(captcha_text)

    # Save image to a file
    image.save("captcha.png")
    print("CAPTCHA image saved as 'captcha.png'.")

    # Display the CAPTCHA image to user (optional, if running on GUI-enabled system)
    try:
        image.show()
    except:
        pass

    user_input = input("Enter CAPTCHA: ")
    if user_input.strip().upper() == captcha_text:
        print("CAPTCHA verification successful!")
    else:
        print("CAPTCHA verification failed!")

if __name__ == "__main__":
    main()

